#!/usr/bin/env python3
"""
train_ann.py

This script trains an Artificial Neural Network (ANN) to predict the optimal scheduling algorithm
for our Intelligent Process Scheduler. The ANN is trained using a synthetic dataset based on three 
features:
    - avg_cpu_usage: Average CPU usage (range: 0.0 to 1.0)
    - avg_burst_time: Average burst time (range: 1.0 to 10.0)
    - avg_io_wait:    Average I/O wait time (range: 0.0 to 5.0)

Labels are determined using simple threshold-based logic:
    - If avg_cpu_usage > 0.8          => "RR"   (Round Robin)
    - Else if avg_burst_time < 5.0     => "SJN"  (Shortest Job Next)
    - Otherwise                     => "FCFS" (First-Come-First-Serve)

The model is a small feed-forward neural network with two hidden layers.
After training, the weights are saved to 'model/ann_weights.bin' in binary format.
"""

import os
import numpy as np
import tensorflow as tf
from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import Dense
from tensorflow.keras.utils import to_categorical

# Set random seeds for reproducibility
np.random.seed(42)
tf.random.set_seed(42)

# -------------------------------
# Generate Synthetic Training Data
# -------------------------------
num_samples = 1000

# Generate synthetic features
cpu_usage = np.random.uniform(0.0, 1.0, num_samples)      # avg_cpu_usage: 0.0 - 1.0
burst_time = np.random.uniform(1.0, 10.0, num_samples)      # avg_burst_time: 1.0 - 10.0
io_wait = np.random.uniform(0.0, 5.0, num_samples)          # avg_io_wait: 0.0 - 5.0

# Stack features into a single input matrix
X = np.stack((cpu_usage, burst_time, io_wait), axis=1)

# Define labels based on threshold logic:
# Label 0: "RR"   if avg_cpu_usage > 0.8
# Label 1: "SJN"  if avg_cpu_usage <= 0.8 and avg_burst_time < 5.0
# Label 2: "FCFS" otherwise
y = np.zeros(num_samples, dtype=int)
for i in range(num_samples):
    if cpu_usage[i] > 0.8:
        y[i] = 0  # "RR"
    elif burst_time[i] < 5.0:
        y[i] = 1  # "SJN"
    else:
        y[i] = 2  # "FCFS"

# Convert labels to one-hot encoding for training
y_categorical = to_categorical(y, num_classes=3)

# -------------------------------
# Build the ANN Model
# -------------------------------
model = Sequential([
    Dense(8, activation='relu', input_shape=(3,)),
    Dense(8, activation='relu'),
    Dense(3, activation='softmax')
])

model.compile(optimizer='adam', loss='categorical_crossentropy', metrics=['accuracy'])
model.summary()

# -------------------------------
# Train the Model
# -------------------------------
history = model.fit(X, y_categorical, epochs=50, batch_size=32, validation_split=0.2, verbose=1)

# Evaluate the model on the entire dataset
loss, accuracy = model.evaluate(X, y_categorical, verbose=0)
print("Final training accuracy: {:.2f}%".format(accuracy * 100))

# -------------------------------
# Save the Model Weights for C-based Inference
# -------------------------------
# Retrieve model weights
weights = model.get_weights()

# Ensure the model directory exists
model_dir = "model"
if not os.path.exists(model_dir):
    os.makedirs(model_dir)

# Save weights as a binary file (using numpy.save which produces a .npy file)
weights_file = os.path.join(model_dir, "ann_weights.bin")
np.save(weights_file, weights)
print(f"Model weights saved to {weights_file}")
