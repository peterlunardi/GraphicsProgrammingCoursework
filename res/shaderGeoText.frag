//Version number
#version 400
//Layout Qualifer
layout( location = 0 ) out vec4 fragcolor;

in vec2 _texCoords;

uniform sampler2D diffuse;


 
void main()
{
//Setting each vector component to uniform varaible then setting final colour
	
    fragcolor = vec4(texture(diffuse, _texCoords));
}