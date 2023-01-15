# 5-Types-of-Distortion Plug-in
This project is a Plug-in that can apply 5 different types of distortion. These are: 'Hard Clip', 'Soft Clip', 'Quarter Cicle' and 'Asymmetric'.
The project is written in C++ using JUCE framework. It has been created using OPP and is Thread safe.
The interface has a menu to select which type of distortion has. It also has knobs to choose the value needed for each type of distortion, these knobs are just visible when that type of distortion is selected.
The interface also has an output gain, and a filter to filter the distorted signal (wet). This filter has a menu to choose between LPF and HPF. The interface also has a Dry/Wet knob to mix the distorted signal with some dry signal.
Each type of distortion is written in a different class. The process for each distortion signal has been achieved based in the Book 'Audio Processes' from  David Creasey.
