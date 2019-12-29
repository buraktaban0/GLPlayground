
#version 330 core

in vec3 color;
in vec2 texCoords;

out vec4 FragColor;

uniform sampler2D tex;

void main()
{

	FragColor = vec4(color, 1.0f);
	FragColor = vec4(texCoords, 0.0f, 1.0f);
	FragColor = texture2D(tex, texCoords);
}