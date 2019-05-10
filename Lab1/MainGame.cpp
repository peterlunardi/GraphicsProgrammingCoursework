#include "MainGame.h"
#include "Camera.h"
#include <iostream>
#include <string>
#include <list>


Transform transform;
Transform transform1;
Mesh water;


float quadVertices[] =
{
-0.5f, 0.5f, 0.0f,
-0.5f, -0.5f, 0.0f,
0.5f, -0.5f, 0.0f,

0.5f, -0.5f, 0.0f,
0.5f, 0.5f, 0.0f,
-0.5f, 0.5f, 0.0f
};

Vertex waterVertices[] =
{
	Vertex(glm::vec3(-0.5, 0.5, 0), glm::vec2(1,1)),
	Vertex(glm::vec3(-0.5, -0.5, 0), glm::vec2(1,1)),
	Vertex(glm::vec3(0.5, -0.5, 0), glm::vec2(1,1)),
	Vertex(glm::vec3(0.5, 0.5, 0), glm::vec2(1,1)),
};

unsigned int waterIndices[] =
{
	0, 1, 3,
	3, 1, 2
};

MainGame::MainGame()
{
	_gameState = GameState::PLAY;
	Display* _gameDisplay = new Display(); //new display
	Mesh* mesh1();
	Mesh* mesh2();
	Mesh* mesh3();
	Mesh* mesh4();
	Mesh* quad();
	//Audio* audioDevice();
	Texture* texture(); //load texture
	Texture* texture1(); //load texture
	Overlay* overlay(); //load texture
	Shader* shader();
	Shader* shaderBlur();
	Shader* shaderToon();
	Shader* shaderRim();
	Shader* shaderReflect();
	Shader* shaderOL();
	Shader* shaderExploding();
}

MainGame::~MainGame()
{
}

void MainGame::run()
{
	initSystems();
	gameLoop();
}

void MainGame::initSystems()
{
	_gameDisplay.initDisplay();
	SDL_SetRelativeMouseMode(SDL_TRUE);
	SDL_CaptureMouse(SDL_TRUE);

	texture.init("..\\res\\grass.jpg"); //load texture
	texture1.init("..\\res\\heart.jpg"); //load texture

	shaderOL.init("..\\res\\shaderOL.vert", "..\\res\\shaderOL.frag");
	shaderSkybox.init("..\\res\\shaderSkybox.vert", "..\\res\\shaderSkybox.frag");
	shader.init("..\\res\\shader.vert", "..\\res\\shader.frag");
	shaderReflect.init("..\\res\\shaderReflection.vert", "..\\res\\shaderReflection.frag");
	shaderExploding.initGeo("..\\res\\shaderGeoText.vert", "..\\res\\shaderGeoText.frag", "..\\res\\shaderGeoText.geom");

	overlay.init("..\\res\\grass.jpg");

	mesh1.loadModel("..\\res\\deer.obj");
	mesh2.loadModel("..\\res\\heart.obj");
	mesh3.loadModel("..\\res\\plane.obj");
	mesh4.loadModel("..\\res\\mountain.obj");

	shaderReflect.Bind();
	shaderReflect.setInt("skybox", 0);

	shaderSkybox.Bind();
	shaderSkybox.setInt("skybox", 0);

	shader.Bind();
	shader.setVec3("lightDirection", glm::vec3(0.5f, -1.0f, 0.5f));
	shader.setVec3("lightColour", glm::vec3(1.0f, 0.95f, 0.95f));
	shader.setVec2("lightBias", glm::vec2(0.1f, 0.9f));

	shaderOL.setVec3("lightPos", glm::vec3(10.0f, 1000, 0));


	myCamera.initCamera(glm::vec3(30, 15, 90), 70.0f, (float)_gameDisplay.getWidth() / _gameDisplay.getHeight(), 0.6f, 2500.0f);
	lastX = _gameDisplay.getWidth() / 2.0f;
	lastY = _gameDisplay.getHeight() / 2.0f;

	counter = 1.0f;
	WAVE_SPEED = 0.0f;

	vector<std::string> faces
	{
		"..\\res\\skybox\\right.jpg",
		"..\\res\\skybox\\left.jpg",
		"..\\res\\skybox\\top.jpg",
		"..\\res\\skybox\\bottom.jpg",
		"..\\res\\skybox\\back.jpg",
		"..\\res\\skybox\\front.jpg"

	};
	cubemapTexture = skybox.loadCubemap(faces); //Load the cubemap using "faces" into cubemapTextures

	float skyboxVertices[] = {
		// positions          
		-1.0f,  1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		-1.0f,  1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f
	};

	//use openGL functionality to generate & bind data into buffers
	glGenVertexArrays(1, &skyboxVAO);
	glGenBuffers(1, &skyboxVBO);
	glBindVertexArray(skyboxVAO);
	glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	//mesh stuff maybe
	water.init(waterVertices, sizeof(waterVertices), waterIndices, sizeof(waterIndices));

}

void MainGame::gameLoop()
{
	while (_gameState != GameState::EXIT)
	{
		//framerate stuff used for movement
		float currentFrame = SDL_GetTicks();
		if (currentFrame > lastFrame)
		{
			deltaTime = (double)(currentFrame - lastFrame);
			lastFrame = currentFrame;
		}

		processInput();
		drawGame();
	}
}

void MainGame::processInput()
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			_gameState = GameState::EXIT;
			break;
		case SDL_MOUSEMOTION:
			int xpos = event.motion.x;
			int ypos = event.motion.y;

			if (firstMouse)
			{
				lastX = xpos;
				lastY = ypos;
				firstMouse = false;
			}

			float xoffset = xpos - lastX;
			float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

			lastX = xpos;
			lastY = ypos;

			myCamera.ProcessMouseMovement(xoffset, yoffset);
		}
	}

	//camera movement stuff
	//its done using keystates so that multiple key presses can be registered and moving the 
	//camera is much smoother than using events
	//NOTE - STILL REQUIRES A POLL EVENT CHECK
	const Uint8* keystates = SDL_GetKeyboardState(NULL);

	if (keystates[SDL_SCANCODE_W])
	{
		myCamera.ProcessKeyboard(FORWARD, deltaTime);

	}
	if (keystates[SDL_SCANCODE_A])
	{
		myCamera.ProcessKeyboard(LEFT, deltaTime);
	}
	if (keystates[SDL_SCANCODE_S])
	{
		myCamera.ProcessKeyboard(BACKWARD, deltaTime);
	}
	if (keystates[SDL_SCANCODE_D])
	{
		myCamera.ProcessKeyboard(RIGHT, deltaTime);
	}
	if (keystates[SDL_SCANCODE_LSHIFT])
	{
		myCamera.ProcessKeyboard(UP, deltaTime);
	}
	if (keystates[SDL_SCANCODE_LCTRL])
	{
		myCamera.ProcessKeyboard(DOWN, deltaTime);
	}
	if (keystates[SDL_SCANCODE_1])
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	if (keystates[SDL_SCANCODE_2])
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
}

void MainGame::Skybox()
{
	glDepthFunc(GL_LEQUAL);  // change depth function so depth test passes when values are equal to depth buffer's content
	shaderSkybox.Bind();
	glm::mat4 view = glm::mat4(glm::mat3(myCamera.GetView())); // remove translation from the view matrix
	shaderSkybox.setMat4("view", view);
	shaderSkybox.setMat4("projection", myCamera.GetProjection());
	// skybox cube
	glBindVertexArray(skyboxVAO);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
	glDepthFunc(GL_LESS); // set depth function back to default
}

void MainGame::meshRender()
{
	shader.Bind();

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(100, 0, 0));
	model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));

	shader.setMat4("view", myCamera.GetView());
	shader.setMat4("projection", myCamera.GetProjection());
	shader.setVec3("cameraPos", myCamera.getPos());
	shader.setInt("skybox", 0);
	shader.setMat4("model", model);

	WAVE_SPEED += 0.0001f * deltaTime ;
	shader.setFloat("waveTime", WAVE_SPEED);

	mesh3.draw();

	//this generates it in code
	//creates a grid of water meshes
	//for (int x = 0; x < 20; x++)
	//{
	//	for (int y = 0; y < 20; y++)
	//	{
	//		model = glm::translate(model, glm::vec3(x, y, 0));
	//		shader.setMat4("model", model);
	//		water.draw();
	//		model = glm::translate(model, glm::vec3(-x, -y, 0));
	//	}
	//}
}

void::MainGame::explode()
{
	shaderExploding.Bind();
	shaderExploding.setFloat("time", 0.5f + counter);
	shaderExploding.Update(transform, myCamera);
	texture1.Bind(0);
	mesh2.draw();
}

void MainGame::setReflection()
{

	//vertex shader uniforms
	shaderReflect.setMat4("model", transform.GetModel());
	shaderReflect.setMat4("view", myCamera.GetView());
	shaderReflect.setMat4("projection", myCamera.GetProjection());

	//fragment shader uniforms
	shaderReflect.setVec3("cameraPos", myCamera.getPos());

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);

}

void MainGame::drawGame()
{
	_gameDisplay.clearDisplay(0.2f, 0.3f, 0.3f, 1.0f);

	transform.SetPos(glm::vec3(20, 0, 0));
	transform.SetRot(glm::vec3(0, sinf(counter), 0));
	transform.SetScale(glm::vec3(6, 6, 6));

	shaderReflect.Bind();
	setReflection();
	mesh1.draw();

	transform.SetPos(glm::vec3(100, -6.0f, 0));
	transform.SetRot(glm::vec3(0, 0, 0));
	transform.SetScale(glm::vec3(5, 5, 5));

	shaderOL.Bind();
	shaderOL.setMat4("MVP", transform.GetMVP(myCamera));
	shaderOL.setVec3("viewPos", myCamera.getPos());
	texture.Bind(0);
	mesh4.draw();

	transform.SetPos(glm::vec3(-10, 7, 5));
	transform.SetRot(glm::vec3(0, 0, 0));
	transform.SetScale(glm::vec3(0.5, 0.5, 0.5));
	explode();

	Skybox();

	glDepthMask(GL_FALSE);

	meshRender();

	glDepthMask(GL_TRUE);

	
	counter = counter + 0.001f * deltaTime;

	glEnableClientState(GL_COLOR_ARRAY);
	glEnd();

	_gameDisplay.swapBuffer();
}

