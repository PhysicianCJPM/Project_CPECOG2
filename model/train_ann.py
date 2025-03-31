#!/usr/bin/env python3

import os
import numpy as np
import tensorflow as tf
from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import Dense, Dropout
from tensorflow.keras.regularizers import l2
from tensorflow.keras.callbacks import EarlyStopping
from tensorflow.keras.utils import to_categorical

# Set random seeds for reproducibility
np.random.seed(42)
tf.random.set_seed(42)

# -------------------------------
# Generate Synthetic Training Data
# -------------------------------
num_samples = 5000  # Increased for better generalization

# Synthetic features
cpu_usage = np.random.uniform(0.0, 1.0, num_samples)
burst_time = np.random.uniform(1.0, 10.0, num_samples)
io_wait = np.random.uniform(0.0, 5.0, num_samples)

X = np.stack((cpu_usage, burst_time, io_wait), axis=1)

y = np.zeros(num_samples, dtype=int)
for i in range(num_samples):
    if cpu_usage[i] > 0.8:
        y[i] = 0  # "RR"
    elif burst_time[i] < 5.0:
        y[i] = 1  # "SJN"
    else:
        y[i] = 2  # "FCFS"

y_categorical = to_categorical(y, num_classes=3)

# -------------------------------
# Build the ANN Model with Regularization
# -------------------------------
model = Sequential([
    Dense(16, activation='relu', input_shape=(3,), kernel_regularizer=l2(0.01)),
    Dropout(0.2),
    Dense(16, activation='relu', kernel_regularizer=l2(0.01)),
    Dropout(0.2),
    Dense(3, activation='softmax')
])

model.compile(optimizer=tf.keras.optimizers.Adam(learning_rate=0.001), 
              loss='categorical_crossentropy', 
              metrics=['accuracy'])
model.summary()

# -------------------------------
# Train the Model with Early Stopping
# -------------------------------
early_stopping = EarlyStopping(monitor='val_loss', patience=10, restore_best_weights=True)
model.fit(X, y_categorical, epochs=200, batch_size=64, validation_split=0.2, verbose=1, callbacks=[early_stopping])

loss, accuracy = model.evaluate(X, y_categorical, verbose=0)
print("Final training accuracy: {:.2f}%".format(accuracy * 100))

# -------------------------------
# Save the Model Weights
# -------------------------------
model_dir = "intelligent-process-scheduler/model"
os.makedirs(model_dir, exist_ok=True)
weights_file = os.path.join(model_dir, "ann_weights.bin")

weights = model.get_weights()
print("Saving weights to:", weights_file)
with open(weights_file, "wb") as f:
    np.array([len(weights)], dtype=np.int32).tofile(f)
    for weight in weights:
        np.array([len(weight.shape)], dtype=np.int32).tofile(f)
        np.array(weight.shape, dtype=np.int32).tofile(f)
        np.array(weight, dtype=np.float32).tofile(f)
print(f"Model weights saved to {weights_file}")
