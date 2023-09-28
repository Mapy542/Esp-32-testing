# compiles every html file in the web folder into a ESP-32 Async Server c++ include file
# this file is then included in the main program and the server is started

import os
import sys

CompiledWebFile = "WebCompiled.h"


def GETpage(page, html, f):
    if page == "index.html":
        page = "/"  # index.html is the default page so we need to change it to "/"
    f.write(
        'server.on("/'
        + str(page[:-5])
        + '", HTTP_GET, [](AsyncWebServerRequest *request){ \n'
        + '   request->send(200, "text/html", "'
        + str(html)
        + '");\n'
        + "});\n\n"
    )


def Response404(page, html, f):
    f.write(
        "server.onNotFound([](AsyncWebServerRequest *request){ \n"
        + '   request->send(404, "text/html", "'
        + str(html)
        + '");\n'
        + "});\n\n"
    )


# get the current directory of the script
cd = os.path.dirname(os.path.abspath(__file__))
# list all files in the web folder
files = os.listdir(cd)

# filter for html files only
files = [f for f in files if f.endswith(".html")]

# open the compiled web file
with open(os.path.dirname(os.path.abspath(__file__)) + "/" + CompiledWebFile, "w") as f:
    # write function header
    f.write("#include <ESPAsyncWebServer.h>\n\n")
    f.write("void AddServerPages(AsyncWebServer &server){\n")

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

            GETpage(page, html, f)  # add the static get response to the file

            # if "</form>" in html:  # add the form post response to the file
            # PostPage(page, html, f)

    # write function footer
    f.write("}\n")
