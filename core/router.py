'''
Core maintains the execution of the main app
'''
import cv2
from flask import Flask, Response, request
import json
import flask_login

app = Flask(__name__)
global image
class VideoCamera(object):
    def __init__(self):
        self.video = cv2.VideoCapture(0)

    def __del__(self):
        self.video.release()

    def get_frame(self):
        success, image = self.video.read()
        ret, jpeg = cv2.imencode('.jpg', image)
        return jpeg.tobytes(),image

def gen(camera):
    global image
    while True:
        frame,image = camera.get_frame()

        yield (b'--frame\r\n'
               b'Content-Type: image/jpeg\r\n\r\n' + frame + b'\r\n')

@app.route('/video_feed')
def video_feed():
    return Response(gen(VideoCamera()),
                    mimetype='multipart/x-mixed-replace; boundary=frame') 


@app.route("/measure", methods=['GET', 'PUT'])
def measure():
    global image    
    import measure    
    print("[+]Getting the current video frame...")
    #cv2.imwrite('core/test.jpg', image)    
    measure.run()    
    return json.dumps(str(open('core/outputs/measurement.txt').readlines()[0]))

    
@app.route('/show_results')
def show_results():
    ret, jpeg = cv2.imencode('.jpg', cv2.imread('core/outputs/draw1.jpg'))
    frame =  jpeg.tobytes()
    yield (b'--frame\r\n'
               b'Content-Type: image/jpeg\r\n\r\n' + frame + b'\r\n')
    
@app.route('/capture', methods=['GET', 'POST'])
def capture():
    cv2.imwrite('core/data/' + request.form['file'] + '.jpg', image) 
@app.route('/train', methods=['GET', 'POST'])
def train():
    import models
    models.train_main_model()   
    


if __name__ == '__main__':
    app.run(host='0.0.0.0', debug=True)
    # measure()
    



