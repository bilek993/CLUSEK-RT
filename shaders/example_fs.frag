#version 450

layout(location = 0) in vec4 InputColor;

layout(location = 0) out vec4 OutputColor;

void main() {
	OutputColor = InputColor;
}