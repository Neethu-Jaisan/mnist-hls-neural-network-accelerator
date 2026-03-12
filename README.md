# MNIST Neural Network Inference Accelerator using Vivado HLS

This project implements a **hardware inference engine for MNIST digit classification** using **Vivado High Level Synthesis (HLS)**.

A neural network trained in TensorFlow is exported to C arrays and integrated into a hardware-oriented C++ design. Vivado HLS synthesizes the design into RTL, demonstrating how machine learning workloads can be mapped onto hardware.

The project shows the complete workflow:

**Model Training → Weight Export → Hardware Inference → HLS Simulation → RTL Synthesis**

---

## Project Overview

The implemented neural network architecture is a simple fully connected network:

* **Input layer:** 784 neurons (flattened 28×28 MNIST image)
* **Hidden layer:** 16 neurons with ReLU activation
* **Output layer:** 10 neurons representing digits 0–9

The inference engine performs the following computation:

```
hidden = ReLU(W1 × input + b1)
output = W2 × hidden + b2
```

Each neuron is computed using **multiply–accumulate (MAC) operations** synthesized into hardware using Vivado HLS.

---

## Hardware Architecture

The design uses a **pipelined MAC computation model**:

1. Input features are streamed into the compute engine.
2. Multiply–accumulate operations compute weighted sums.
3. ReLU activation is applied to the hidden layer.
4. The output layer computes classification logits.

The inner computation loop is pipelined using HLS pragmas, enabling efficient reuse of compute resources.

---

## HLS Resource Utilization

Example synthesis results on **Artix-7 (xc7a35t)**:

| Resource | Usage |
| -------- | ----- |
| DSP48    | 3     |
| BRAM     | 33    |
| LUT      | 1191  |
| FF       | 1050  |

The design demonstrates **efficient hardware reuse**, performing large matrix-vector computations with minimal DSP resources.

---

## Example Simulation Output

```
Logits:
3.25566 -5.69816 4.35207 7.61336 -3.52966
2.38963 -13.1815 13.9525 1.18589 2.07052

Predicted digit: 7
True digit: 7
Prediction correct!
```

This confirms that the hardware inference pipeline correctly classifies MNIST digits.

---

## Project Flow

```
MNIST dataset
      ↓
TensorFlow model training
      ↓
Export trained weights to C arrays
      ↓
Vivado HLS inference engine
      ↓
C Simulation (CSIM)
      ↓
RTL synthesis
```

---

## Repository Structure

```
mnist-hls-neural-network-accelerator
│
├── hls
│   ├── inference.cpp        # HLS neural network inference engine
│   ├── tb.cpp               # Testbench for simulation
│   └── weights.h            # Exported trained weights
│
├── training
│   └── train_mnist_model.ipynb
│
├── docs
│   └── architecture.png
│
└── README.md
```

---

## Running the Project

1. Open **Vivado HLS**
2. Create a new project
3. Add files from the `hls` directory
4. Set the top function:

```
inference
```

5. Run:

```
C Simulation
C Synthesis
```

---

## Future Improvements

This project can be extended in several ways:

* Implement **fixed-point quantization** using `ap_fixed`
* Design a **systolic array matrix multiplication engine**
* Add **loop tiling and parallel processing elements**
* Extend the design to support **convolutional neural networks**
* Deploy the synthesized design on an **FPGA board**

---

## Author

**Neethu Jaisan**
M.Tech VLSI Design

