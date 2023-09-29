# compiles every html file in the web folder into a ESP-32 Async Server c++ include file
# this file is then included in the main program and the server is started

import os

CompiledWebFile = "WebCompiled.h"


def GETpage(page, html, ExtraIncludes, f):
    if page == "index.html":
        page = "/"  # index.html is the default page so we need to change it to "/"
    f.append(
        'server.on("/'
        + str(page[:-5])
        + '", HTTP_GET, [](AsyncWebServerRequest *request){ \n'
        + ExtraIncludes
        + "\n"
        + '   request->send(200, "text/html", "'
        + str(html)
        + '");\n'
        + "});\n\n"
    )


def POSTpage(page, html, ExtraIncludes, f):
    if page == "index.html":
        page = "/"  # index.html is the default page so we need to change it to "/"

    # get the inputs from the html file
    inputs = html.split("<input")
    inputs.pop(0)  # remove the first element because it is not an input
    inputnames = []
    inputtypes = []

    for i in inputs:
        if 'type=\\"submit\\"' in i:  # ignore submit buttons as they are not inputs
            continue
        # get the name of the input
        inputnames.append(i.split('name=\\"')[1].split('\\"')[0])
        # get the type of the input
        inputtypes.append(i.split('type=\\"')[1].split('\\"')[0])

    # create external variables for the input names
    # appended at the second line of the file

    uniqueinputnames = []
    uniqueinputtypes = []
    for i in range(len(inputnames)):
        if inputnames[i] not in uniqueinputnames:
            uniqueinputnames.append(inputnames[i])
            uniqueinputtypes.append(inputtypes[i])

    for i in range(len(uniqueinputnames)):
        f.insert(1, " String " + str(uniqueinputnames[i]) + ";\n")

    f.append(
        'server.on("/'
        + str(page[:-5])
        + '", HTTP_POST, [](AsyncWebServerRequest *request) {\n'
    )

    for i in uniqueinputnames:
        f.append("  " + i + ' = request->arg("' + i + '");\n')

    f.append(ExtraIncludes + "\n")

    f.append('request->send(200, "text/html", "' + str(html) + '");\n' + "});\n\n")


def Response404(page, html, f):
    f.append(
        "server.onNotFound([](AsyncWebServerRequest *request){ \n"
        + '   request->send(404, "text/html", "'
        + str(html)
        + '");\n'
        + "});\n\n"
    )


def ShowCurrentInHTML(html):
    # modify the html file to show the current values of the inputs
    inputs = html.split("<input")
    InputsPrecursor = inputs[0]
    inputs.pop(0)  # remove the first element because it is not an input

    ExtraIncludes = ""
    for i in range(len(inputs)):
        if (
            'type=\\"submit\\"' in inputs[i]
        ):  # ignore submit buttons as they are not inputs
            continue
        # get the name of the input
        inputname = inputs[i].split('name=\\"')[1].split('\\"')[0]
        inputtype = inputs[i].split('type=\\"')[1].split('\\"')[0]
        if 'value=\\"' in inputs[i]:
            # get the value of the input
            inputvalue = inputs[i].split('value=\\"')[1].split('\\"')[0]
        else:
            inputvalue = ""

        print(inputname, inputtype, inputvalue)

        if inputtype == "text" or inputtype == "number":
            # add a value attribute to the input
            inputs[i] = (
                inputs[i].split(">")[0]
                + ' value=" + '
                + inputname
                + ' + ">'
                + ">".join(inputs[i].split(">")[1:])
            )
        elif inputtype == "checkbox" or inputtype == "radio":
            print("checkbox")
            inputs[
                i
            ] = (  # inject a string variable into the html file. This variable will contain "checked" if the input is checked and "" if it is not
                inputs[i].split(">")[0]
                + ' " + '
                + inputvalue
                + ' + ">'
                + ">".join(inputs[i].split(">")[1:])
            )
            ExtraIncludes = ExtraIncludes + (
                " String "
                + inputvalue
                + ";\n"
                + " if ("
                + inputname
                + '.equals("'
                + inputvalue
                + '")){\n'
                + "   "
                + inputvalue
                + ' = "checked";\n'
                + " }else{\n"
                + "   "
                + inputvalue
                + ' = "";\n'
                + " }\n"
            )

    # reassemble the html file
    html = InputsPrecursor + "<input" + "<input ".join(inputs)
    print(ExtraIncludes)
    return html, ExtraIncludes


# get the current directory of the script
cd = os.path.dirname(os.path.abspath(__file__))
# list all files in the web folder
files = os.listdir(cd)

# filter for html files only
files = [f for f in files if f.endswith(".html")]

# open the compiled web file
with open(
    os.path.dirname(os.path.abspath(__file__)) + "/" + CompiledWebFile, "w"
) as CompileFile:
    f = []
    # write function header
    f.append("#include <ESPAsyncWebServer.h>\n\n")
    f.append("void AddServerPages(AsyncWebServer &server){\n")

    for page in files:
        # open the html file
        with open(
            os.path.dirname(os.path.abspath(__file__)) + "/" + page, "r"
        ) as html:  # do basic cleanup
            # read the file
            html = html.read()
            # remove newlines
            html = html.replace("\n", "")
            # remove tabs
            html = html.replace("\t", "")
            # remove double spaces
            html = html.replace("  ", "")
            # remove backslashes
            html = html.replace("\\", "\\\\")
            # remove double quotes
            html = html.replace('"', "\\" + '"')
            # remove single quotes
            html = html.replace("'", "\\" + "'")

            if page == "404.html":  # add custom 404 page if it exists
                Response404(page, html, f)
                continue

            if "</form>" in html:  # if theres a input form in the html file
                if (
                    "<!--SHOW CURRENT-->" in html.split("<form")[1]
                ):  # if the form should show the current values of the inputs
                    EditedHTML, ExtraIncludes = ShowCurrentInHTML(
                        html
                    )  # get the edited html
                else:
                    EditedHTML = html
                    ExtraIncludes = ""

                POSTpage(
                    page, EditedHTML, ExtraIncludes, f
                )  # add the post response to the file
            else:
                EditedHTML = html
                ExtraIncludes = ""

            GETpage(
                page, EditedHTML, ExtraIncludes, f
            )  # add the static get response to the file

    # write function footer
    f.append("}\n")

    # write the file
    CompileFile.writelines(f)
