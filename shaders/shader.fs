#version 330 core

out vec4 FragColor;

uniform float alpha;

in vec3 ourColor;

void main()
{
    FragColor = vec4(ourColor.xy, alpha, 1.0);
}
