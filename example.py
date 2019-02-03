from keras.models import load_model
model = load_model('yolo.h5')

for layer in model.layers:
    layer.trainable = False
