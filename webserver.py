from flask import Flask, request


app = Flask(__name__)
l = []


@app.route('/')
def index():
    return 'OK', 200


@app.route('/get-sensor', methods=['GET'])
def data():
    if request.method == 'GET':
        args = request.args
        temperature = args.get('temperature')
        l.append(temperature)
        return temperature
    else:
        return 'Wrong'


@app.route('/get')
def data1():
    sensor_data = '<ul>'
    for item in l:
        sensor_data += f'<li>{item}</li>'
    sensor_data += '</ul>'
    return sensor_data


if __name__ == '__main__':
    app.run(debug=True, port=8000, host='0.0.0.0')
