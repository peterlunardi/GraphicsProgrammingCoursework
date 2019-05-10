//Version number
#version 330 core

//Layout qualfier
layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;


//Uniform variabe
uniform float time;

in VS_OUT {
	vec2 texCoords;
} gs_in[];

out vec2 _texCoords;

vec4 explode(vec4 position, vec3 normal)
{
//Amout of explosion
    float magnitude = 10.0;
	//Direction of explosion, going along normal
    vec3 direction = normal * ((sin(time) + 1.0) / 2.0) * magnitude; 
	//Returning position
    return position + vec4(direction, 0.0);
}

vec3 GetNormal()
{
//Getting the normal vector of each vertex
   vec3 a = vec3(gl_in[0].gl_Position) - vec3(gl_in[1].gl_Position);
   vec3 b = vec3(gl_in[2].gl_Position) - vec3(gl_in[1].gl_Position);
   //returns the cross product between the two vectors calculated
   return normalize(cross(a, b));
}

void main()
{
//Getting normal
    vec3 normal = GetNormal();
//Setting current vertex position

	for(int i = 0; i < gl_in.length(); i++)
	{
		_texCoords = gs_in[i].texCoords;
		gl_Position = explode(gl_in[i].gl_Position, normal);
		EmitVertex();
	}
    
    EndPrimitive();
}  