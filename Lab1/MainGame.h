#pragma once
#include <SDL\SDL.h>
#include <GL/glew.h>
#include "Display.h" 
#include "Shader.h"
#include "Mesh.h"
#include "Texture.h"
#include "transform.h"
#include "Audio.h"
#include "Overlay.h"

enum class GameState{PLAY, EXIT};

class MainGame
{
public:
	MainGame();
	~MainGame();

	void run();

private:

	void initSystems();
	void processInput();
	void gameLoop();
	void drawGame();
	void setReflection();

	void Skybox();

	void meshRender();

	void explode();

	GLuint skyboxVAO, skyboxVBO, cubemapTexture;
	GLuint meshVAO, meshVBO;
	vector<std::string> faces;

	Display _gameDisplay;
	GameState _gameState;
	Mesh mesh1;
	Mesh mesh2;
	Mesh mesh3;
	Mesh mesh4;
	Mesh quad;

	Texture texture;
	Texture texture1;
	Texture skybox;

	Overlay overlay;
	Shader shader;
	Shader shaderBlur;
	Shader shaderToon;
	Shader shaderRim;
	Shader shaderSkybox;
	Shader shaderReflect;
	Shader shaderOL;
	Shader shaderExploding;

	glm::mat4 modelView;

	//camera stuff
	Camera myCamera;
	float lastX;
	float lastY;
	bool firstMouse = true;

	//Audio audioDevice;

	float counter;
	float WAVE_SPEED;
	unsigned int whistle;
	unsigned int backGroundMusic;

	float deltaTime;
	float lastFrame;
};

