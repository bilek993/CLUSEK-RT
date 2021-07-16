#version 450

layout(location = 0) in vec3 Position;

layout(location = 0) out vec4 Color;

void main()
{
    gl_Position = vec4(Position, 1.0);
    Color = vec4(Position + vec3(0.5f, 0.5f, 0.5f), 1.0);
}