import subprocess
from flask import Flask
app = Flask(__name__)

@app.route("/")
def hello():
    subprocess.call(['/usr/bin/lpr', '-PUSB_Thermal_Printer_LOCAL', '-o', 'raw', 'test.txt'])
    return "Hello World!"

if __name__ == "__main__":
    app.run()
