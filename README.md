# Assignment-2-JUCE-Project
Assignment 2 by Dr. Elramly using JUCE framework


# 🎵 Advanced Audio Player (JUCE Framework)

> A high-performance, cross-platform desktop audio application built with C++ and JUCE, designed for low-latency signal playback, dynamic waveform rendering, and intuitive playback controls.

---

## 📸 Overview

This **Advanced Audio Player** is a lightweight desktop music and audio application engineered to showcase modern C++ OOP principles and low-level digital signal handling. Built on top of the industry-standard **JUCE framework**, it manages real-time audio threads cleanly while maintaining a responsive, hardware-accelerated user interface.

---

## ✨ Key Features

- 🎧 **Multi-Format Playback:** Native decoding and playback support for standard audio formats (`.mp3`, `.wav`, `.aiff`, `.flac`).
- 🎚️ **Low-Latency Transport Controls:** Real-time Play, Pause, Stop, Fast-Forward, Rewind, and Track Seeking capabilities.
- 🔊 **Volume & Gain Management:** Precision output gain sliders to prevent clipping and manage volume curves.
- ⏩ **Variable Speed Control:** Dynamic playback pitch and speed manipulation without breaking thread synchronization.
- 📊 **Real-Time Waveform Display:** Visual track representation with interactive playhead tracking and seeking.
- 🔁 **Looping & Queue Management:** A flexible playlist system supporting custom track looping and continuous playback.

---

## 🛠️ Tech Stack & Architecture

- **Language:** C++ (C++17 / C++20)
- **Framework:** [JUCE Framework](https://juce.com/) (Audio, GUI, and Core modules)
- **Audio Architecture:**
  - `AudioFormatManager` for dynamic file decoding.
  - `AudioTransportSource` for playback transport control.
  - `AudioAppComponent` for lifecycle and thread-safe audio callback handling (`getNextAudioBlock`).
- **Design Patterns:** Component Observer Pattern, RAII for audio resource management.

---

## 🚀 Getting Started

### Prerequisites

To compile and run this JUCE application locally, ensure you have:
- **C++ Compiler:** `g++`, `clang++`, or MSVC with C++17 support.
- **JUCE Framework:** Download and install JUCE (v7.0+ recommended) or use **Projucer**.
- **IDE Support:** Visual Studio (Windows), Xcode (macOS), or CLion/VS Code with CMake.

### Building via Projucer

1. Clone the repository:
   ```bash
   git clone [https://github.com/your-username/JUCE-Audio-Player.git](https://github.com/your-username/JUCE-Audio-Player.git)
   cd JUCE-Audio-Player
