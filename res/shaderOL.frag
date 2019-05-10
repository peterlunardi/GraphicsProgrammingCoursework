    #version 330 core
	out vec4 FragColor;

	in vec2 _texcoord;
	in vec3 FragPos;
	in vec3 FragNorm;

	uniform vec3 lightPos;
	uniform vec3 viewPos;
	uniform sampler2D ourTexture;

    void main()
    {
        vec3 color = texture(ourTexture, _texcoord).rgb;

		vec3 ambient = 0.9 * color;

		vec3 lightDir = normalize(lightPos - FragPos);
		vec3 normal = normalize(FragNorm);
		float diff = max(dot(lightDir, normal), 0.0);
		vec3 diffuse = diff * color;

		// specular
		vec3 viewDir = normalize(viewPos - FragPos);
		vec3 reflectDir = reflect(-lightDir, normal);
		float spec = 0.0;

		vec3 halfwayDir = normalize(lightDir + viewDir);  
        spec = pow(max(dot(normal, halfwayDir), 0.0), 32.0);

		vec3 specular = vec3(0.5) * spec;
		FragColor = vec4(ambient + diffuse + specular, 1.0);
    }