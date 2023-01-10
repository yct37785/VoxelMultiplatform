#version 460 core
out vec4 FragColor;

in vec4 vertexColor; // the input variable from the vertex shader (same name and same type)

void main()
{
    FragColor = vec4(vertexColor.rgb, 1.0);
}