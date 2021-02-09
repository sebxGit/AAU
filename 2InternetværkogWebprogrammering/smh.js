let title, heading, demoString;

function renderPage(title, heading, demoString){
    var html = '    <!DOCTYPE html>\n' +
'<html lang="da">\n' +
'  <head>\n' +
'    <meta charset="utf-8">\n' +
'    <title>' + title + '</title>\n' +
'  </head>\n' +
'  <body>\n' +
'    <!-- page content -->\n' +
'    <h1> ' + heading + '</h1>\n' +
'    <script>\n' +
'      console.log("' + demoString +'");\n' +
'    </script>\n' +
'  </body>\n' +
'</html>\n';
console.log(html);
}
renderPage("Simpel IWP Demo", "IWP demo","JS Script er kørt");