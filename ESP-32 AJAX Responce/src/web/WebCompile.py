# compiles every html file in the web folder into a ESP-32 Async Server c++ include file
# this file is then included in the main program and the server is started

import os

CompiledWebFile = "WebCompiled.h"
Minify = False  # remove all unnecessary characters from the html file if set to True


def GETpage(page, html, ExtraIncludes, f):
    # creates a simple get response for the html file
    # can include extra includes and code in the lambda function
    # may not be static if HTML is modified to show a current variable value

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
    # creates a post response for the html file
    # can include extra includes and code in the lambda function
    # may not be static if HTML is modified to show a current variable value

    if page == "index.html":
        page = "/"  # index.html is the default page so we need to change it to "/"

    # get the inputs from the html file
    inputs = html.split("<input")
    inputs.pop(0)  # remove the first element because it is not an input
    InputNames = []
    InputTypes = []

    for i in inputs:
        if 'type=\\"submit\\"' in i:  # ignore submit buttons as they are not inputs
            continue
        # get the name of the input
        InputNames.append(i.split('name=\\"')[1].split('\\"')[0])
        # get the type of the input
        InputTypes.append(i.split('type=\\"')[1].split('\\"')[0])

    # remove duplicate inputs (radio buttons and checkboxes have the same name but different values)
    uniqueInputNames = []
    uniqueInputTypes = []
    for i in range(len(InputNames)):
        if InputNames[i] not in uniqueInputNames:
            uniqueInputNames.append(InputNames[i])
            uniqueInputTypes.append(InputTypes[i])

    for i in range(
        len(uniqueInputNames)
    ):  # add global string variables for each input before the AddServerPages function
        if (
            " String " + str(uniqueInputNames[i]) + ";\n" not in f
        ):  # if the variable has not already been added, some forms may have the same input names
            f.insert(1, " String " + str(uniqueInputNames[i]) + ";\n")

    f.append(  # add the post response to the file
        'server.on("/'
        + str(page[:-5])
        + '", HTTP_POST, [](AsyncWebServerRequest *request) {\n'
    )

    for (
        i
    ) in (
        uniqueInputNames
    ):  # parse the request arguments and store them in the global variables
        f.append("  " + i + ' = request->arg("' + i + '");\n')

    f.append(ExtraIncludes + "\n")  # add extra includes if required

    f.append(
        'request->send(200, "text/html", "' + str(html) + '");\n' + "});\n\n"
    )  # finish the post response


def AJAXresponse(RequestName, RequestVars, f):
    # creates a simple get response for ajax request
    # responds with the string data of the request variables separated by commas

    for i in RequestVars:
        # add global string variables for each input before the AddServerPages function
        if " String " + str(i) + ";\n" not in f:
            # if the variable has not already been added, some forms may have the same input names
            f.insert(1, " String " + str(i) + ";\n")

    CSVRequestVars = ' + "," + '.join(
        RequestVars
    )  # create a csv string of the request variables

    f.append(  # add the get response to the file
        'server.on("/'
        + str(RequestName)
        + '", HTTP_GET, [](AsyncWebServerRequest *request){ \n'
        + '   request->send(200, "text/html", '
        + str(CSVRequestVars)
        + ");\n"
        + "});\n\n"
    )


def Response404(html, f):
    # creates a 404 response for the html file
    # is a static response

    f.append(
        "server.onNotFound([](AsyncWebServerRequest *request){ \n"
        + '   request->send(404, "text/html", "'
        + str(html)
        + '");\n'
        + "});\n\n"
    )


def ShowCurrentInHTML(html):
    # modify the html file to show the current values of the inputs of forms
    # returns the modified html file and the extra includes required to do so

    # get the inputs from the html file
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
        InputName = inputs[i].split('name=\\"')[1].split('\\"')[0]
        InputType = inputs[i].split('type=\\"')[1].split('\\"')[0]
        if 'value=\\"' in inputs[i]:
            # get the value of the input
            InputValue = inputs[i].split('value=\\"')[1].split('\\"')[0]
        else:
            InputValue = ""

        if InputType == "text" or InputType == "number":
            # add a value attribute to the input
            inputs[i] = (
                inputs[i].split(">")[0]
                + ' value=" + '
                + InputName
                + ' + ">'
                + ">".join(inputs[i].split(">")[1:])
            )
        elif InputType == "checkbox" or InputType == "radio":
            inputs[
                i
            ] = (  # inject a string variable into the html file. This variable will contain "checked" if the input is checked and "" if it is not
                inputs[i].split(">")[0]
                + ' " + '
                + InputValue
                + ' + ">'
                + ">".join(inputs[i].split(">")[1:])
            )
            ExtraIncludes = ExtraIncludes + (
                " String "
                + InputValue
                + ";\n"
                + " if ("
                + InputName
                + '.equals("'
                + InputValue
                + '")){\n'
                + "   "
                + InputValue
                + ' = "checked";\n'
                + " }else{\n"
                + "   "
                + InputValue
                + ' = "";\n'
                + " }\n"
            )

    # reassemble the html file
    html = (
        InputsPrecursor + "<input" + "<input ".join(inputs)
    )  # extra "<input" is added to the end of the precursor because it was removed in the split and not added back in the join
    return html, ExtraIncludes


def MinifyHTML(html):  # remove all unnecessary characters from the html file
    # remove newlines
    html = html.replace("\n", "")
    # remove tabs
    html = html.replace("\t", "")
    # remove double spaces
    html = html.replace("  ", "")

    return html


def CleanSyntax(html):  # modify the html file to be compatible with c++ as a string
    # remove backslashes
    html = html.replace("\\", "\\\\")
    # remove double quotes
    html = html.replace('"', "\\" + '"')
    # remove single quotes
    html = html.replace("'", "\\" + "'")

    return html


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
    f = []  # create a list to store the file contents
    # useful for inserting lines at specific positions

    # write function header
    f.append("#include <ESPAsyncWebServer.h>\n\n")
    # global vars are inserted here when appropriate
    f.append("void AddServerPages(AsyncWebServer &server){\n")

    for page in files:  # for every html file in the web folder
        # open the html file
        with open(
            os.path.dirname(os.path.abspath(__file__)) + "/" + page, "r"
        ) as html:  # do basic cleanup
            # read the file
            html = html.read()

            html = MinifyHTML(
                html
            )  # remove unnecessary characters if required (messes up formatting just use it)

            html = CleanSyntax(
                html
            )  # make the html file compatible with c++ (required)

            if page == "404.html":  # add custom 404 page if it exists
                Response404(html, f)
                continue

            if "</form>" in html:  # if theres a input form in the html file
                if (
                    "<!--SHOW CURRENT-->" in html.split("<form")[1]
                ):  # if the form should show the current values of the inputs on load
                    EditedHTML, ExtraIncludes = ShowCurrentInHTML(
                        html
                    )  # get the edited html
                    # extra includes are added to lambda function after the request arguments are parsed
                    # this can allow for processing as required of those arguments

                else:
                    EditedHTML = html
                    ExtraIncludes = ""

                POSTpage(
                    page, EditedHTML, ExtraIncludes, f
                )  # add the post response to the file

            else:
                EditedHTML = html  # if there is no form, just add the get response
                ExtraIncludes = ""

            GETpage(
                page, EditedHTML, ExtraIncludes, f
            )  # add the static get response to the file

            if "XMLHttpRequest" in html:  # if there is an ajax request in the html file
                RequestNames = []  # get the names of the requests
                RequestVars = (
                    []
                )  # get the names of the variables that store the response data

                inc = 0
                for i in html.split("XMLHttpRequest();")[1:]:
                    # get the request names and variable names for each request
                    for j in i.split("open(")[1:]:
                        # get the name of the request. should only be one open per request
                        RequestNames.append(j.split(', \\"')[1].split('\\"')[0])

                    RequestVars.append([])
                    for l in i.split(".getElementById")[1:]:
                        # get the name of the variable that stores the response data returned by the request
                        # there should be one variable per getElementById, and there should be multiple vars per request to save bandwidth
                        RequestVars[inc].append(l.split('(\\"')[1].split('\\"')[0])
                    inc += 1

                for i in range(len(RequestNames)):
                    # add the ajax responses to the file
                    AJAXresponse(RequestNames[i], RequestVars[i], f)

    # write function footer
    f.append("}\n")

    # write the file
    CompileFile.writelines(f)
