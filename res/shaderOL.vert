    #version 330 core

	layout (location = 0) in vec3 aPos;
	layout (location = 1) in vec2 texCoord;
	layout (location = 2) in vec3 aNormal;

    out vec2 _texcoord;
	out vec3 FragPos;
	out vec3 FragNorm;

	uniform mat4 MVP;

    void main()
    {
        _texcoord = texCoord * 11.4;
		FragPos = aPos;
		FragNorm = aNormal;
        gl_Position = MVP * vec4(aPos, 1.0);
    }