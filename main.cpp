#include "main.h"
#include "Bunny.h"
#include "Cube.h"
#include "Moon.h"
#include "Sun.h"
#include "Earth.h"
#include "skybox.h"


double XMousePosition, YMousePosition;
GLFWwindow* window;

float ScaleX = 1.0f;
float ScaleY = 1.0f;

float RotateZ = 0.0f;
float RotateX = 0.0f;
float RotateY = 0.0f;

float TransformX = 0.0f;
float TransformY = 0.2f;

float prevTime = 0.0f;
float deltaTime = 0.0f;

bool setOrtho = false;
bool setPers = true;
int  pauseCycle = 0;

float xSpeed = 1.0f;
float xFactor = 0.0f;


glm::vec3 cameraPos = glm::vec3(0.0f, 0.5f, 4.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
glm::vec3 cameraRight = glm::normalize(glm::cross(cameraFront, cameraUp));
glm::vec3 cameraUpView = glm::normalize(glm::cross(cameraFront, cameraRight));

void mouse_callback(GLFWwindow* window, double xpos, double ypos);

float LastX = 1024.0f / 2.0f;
float LastY = 768.0f / 2.0f;

float yaw = -90.0f;
float pitch = 0.0f;

bool firstMouse = true;

void processInput() {

	float cameraSpeed = 2.0f * deltaTime;
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		//eyefront = eyefront - 0.01f;
		cameraPos += cameraSpeed * cameraFront;
		std::cout << "W" << std::endl;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		cameraPos -= cameraRight * cameraSpeed;
		std::cout << "A" << std::endl;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		cameraPos -= cameraSpeed * cameraFront;
		std::cout << "S" << std::endl;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		cameraPos += cameraRight * cameraSpeed;
		std::cout << "D" << std::endl;
	}
	/*
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
		cameraPos -= cameraUpView * cameraSpeed;
		
	}
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
		cameraPos += cameraUpView * cameraSpeed;
		
	}
	*/
	if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS) {
		if (pauseCycle == 0) {
			pauseCycle = 1;
		}
		else if (pauseCycle == 1){
			pauseCycle = 0;
		}
		std::cout << "P pressed - time paused	" << std::endl;
	}

	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
		if (setPers) {
			setOrtho = true;
			setPers = false;
		}
		else if (setOrtho) {
			setPers = true;
			setOrtho = false;
		}
	}

	//movemouse();
	
	
	
}

int main() {
	//stbi_set_flip_vertically_on_load(true);
#pragma region Initialization
	
	window = initialize();
	
#pragma endregion
#pragma region Mesh Loading

	InitializeEarth();
	InitializeMoon();
	InitializeSun();

	std::vector<std::string> faces{
		"right.png",
		"left.png",
		"top.png",
		"bottom.png",
		"front.png",
		"back.png"
	};

	SkyboxData skybox = LoadSkybox("Skybox", faces);

	//InitializeCube();
#pragma endregion

#pragma region Shader Loading

	GLuint skyboxShader = LoadShaders("Shaders/skybox_vertex.shader", "Shaders/skybox_fragment.shader");

	GLuint shaderProgram = LoadShaders("Shaders/Phong_vertex.shader", "Shaders/Phong_directional_fragment.shader");
	
	glUseProgram(shaderProgram);
	GLuint colorLoc = glGetUniformLocation(shaderProgram, "uniformColor");
	glUniform3f(colorLoc, 1.0f, 1.0f, 1.0f);

	GLuint modeltransformLoc = glGetUniformLocation(shaderProgram, "u_model");
	GLuint viewLoc = glGetUniformLocation(shaderProgram, "u_view");
	GLuint projectionLoc = glGetUniformLocation(shaderProgram, "u_projection");

	GLuint normalTransformLoc = glGetUniformLocation(shaderProgram, "u_normal");
	GLuint cameraPosLoc = glGetUniformLocation(shaderProgram, "u_camera_pos");
	GLuint ambientColorLoc = glGetUniformLocation(shaderProgram, "u_ambient_color");
	glUniform3f(ambientColorLoc, 0.1f, 0.1f, 0.1f);

	glm::mat4 trans = glm::mat4(1.0f);
	glUniformMatrix4fv(modeltransformLoc, 1, GL_FALSE, glm::value_ptr(trans));


	glm::mat4 projection = glm::mat4(1.0f);
	//glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
	
	GLuint lightPoscLoc = glGetUniformLocation(shaderProgram, "u_light_post");
	GLuint lightDirLoc = glGetUniformLocation(shaderProgram, "u_light_dir");
	glUniform3f(lightPoscLoc, 1.0f, 1.0f, 0.0f);
	glUniform3f(lightDirLoc, 0.0f, 0.0f, 0.0f);

#pragma endregion

	// set bg color to green
	glClearColor(0.4f, 0.4f, 0.0f, 0.0f);
	
	float slowDown = 0.0f;
	float fovy = 90.0f;
	bool increaseOnce = true;
	
	glm::mat4 orientation = glm::mat4(1.0f);

	glm::mat4 position = glm::mat4(1.0f);
	
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);
	while (!glfwWindowShouldClose(window)) {
		float ratio;
		int width, height;
		
#pragma region InputSystem
		//glfwGetCursorPos(window, &XMousePosition, &YMousePosition);
		processInput();
		glfwSetCursorPosCallback(window, mouse_callback);
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		trans = glm::mat4(1.0f);
		float currentTime = glfwGetTime();
		/*
		if (xFactor > 1.0f) {
			xSpeed = -1.0f;
		}
		else if (xFactor < -1.0f) {
			xSpeed = 1.0f;
		}
		*/
		if (pauseCycle == 0) {
			//Implementation of day/night cycle
			deltaTime = currentTime - prevTime;
			xFactor += deltaTime * xSpeed;
			glUniform3f(lightDirLoc, glm::sin(xFactor * 2), glm::cos(xFactor * 2), 0.0f);
		}
		prevTime = currentTime;

		
#pragma endregion

		glfwGetFramebufferSize(window, &width, &height);
		ratio = width / (float)height;
		GLsizei viewportSize = 0.0f;
		if (ratio > 1.0f) {
			viewportSize = width;
		}
		else {
			viewportSize = height;
		}

		glViewport(0, 0, viewportSize, viewportSize);

#pragma region View
		
		
	
#pragma endregion
		
		glm::mat4 view = glm::lookAt(
			cameraPos,
			cameraPos + cameraFront,
			cameraUp
		);
		
		glUniform3f(cameraPosLoc, cameraPos.x, cameraPos.y, cameraPos.z);
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));


		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//toggle to render wit GL_FILL or GL_LINE
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

#pragma region Draw

		DrawSkyBox(skybox, skyboxShader, view, projection);

		BindEarthArray();
		glUseProgram(shaderProgram);
		/*
		if (setOrtho) {
			projection = glm::ortho(0.0f, (GLfloat)width, 0.0f, (GLfloat)height * 2, 0.1f, 10.0f);
		}
		else if (setPers) {
			projection = glm::perspective(glm::radians(fovy), ratio, 0.1f, 15.0f);
		}
		*/
		//normalTrans = glm::transpose(glm::inverse(trans));

		projection = glm::perspective(glm::radians(fovy), ratio, 0.1f, 15.0f);
		glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

		trans = glm::mat4(1.0f);
		trans = glm::translate(trans, glm::vec3(TransformX, -1.0f, 0.0f));
		//glm::angleAxis(glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		trans = glm::scale(trans, glm::vec3(ScaleX, ScaleY, 1.0f));
		trans = glm::rotate(trans, glm::radians(RotateX), glm::vec3(1.0f, 0.0f, 0.0f));
		trans = glm::rotate(trans, glm::radians(RotateY), glm::vec3(0.0f, 1.0f, 0.0f));
		trans = glm::rotate(trans, glm::radians(RotateZ), glm::vec3(0.0f, 0.0f, 1.0f));
		glm::mat4 normalTrans = glm::transpose(glm::inverse(trans));

		glUniformMatrix4fv(normalTransformLoc, 1, GL_FALSE, glm::value_ptr(normalTrans));
		glUniformMatrix4fv(modeltransformLoc, 1, GL_FALSE, glm::value_ptr(trans));

		DrawEarth();
		/*
		BindMoonArray();

		trans = glm::mat4(1.0f);
		trans = glm::translate(trans, glm::vec3(TransformX, TransformY, -5.0f));
		//glm::angleAxis(glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		trans = glm::scale(trans, glm::vec3(ScaleX, ScaleY, 1.0f));
		trans = glm::rotate(trans, glm::radians(RotateX), glm::vec3(1.0f, 0.0f, 0.0f));
		trans = glm::rotate(trans, glm::radians(RotateY), glm::vec3(0.0f, 1.0f, 0.0f));
		trans = glm::rotate(trans, glm::radians(RotateZ), glm::vec3(0.0f, 0.0f, 1.0f));

		glUniformMatrix4fv(normalTransformLoc, 1, GL_FALSE, glm::value_ptr(normalTrans));
		glUniformMatrix4fv(modeltransformLoc, 1, GL_FALSE, glm::value_ptr(trans));
		DrawMoon();
		*/
		BindSunArray();

		trans = glm::mat4(1.0f);
		trans = glm::translate(trans, glm::vec3(TransformX, -1.0f, 0.0f));
		//glm::angleAxis(glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		trans = glm::scale(trans, glm::vec3(ScaleX, ScaleY, 1.0f));
		trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		trans = glm::rotate(trans, glm::radians(RotateY), glm::vec3(0.0f, 1.0f, 0.0f));
		trans = glm::rotate(trans, glm::radians(RotateZ), glm::vec3(0.0f, 0.0f, 1.0f));

		glUniformMatrix4fv(normalTransformLoc, 1, GL_FALSE, glm::value_ptr(normalTrans));
		glUniformMatrix4fv(modeltransformLoc, 1, GL_FALSE, glm::value_ptr(trans));

		DrawSun();

		//DrawCube();
		
		

		//--- stop drawing here ---

		glfwSwapBuffers(window);
#pragma endregion
		//listen for glfw input events
		glfwPollEvents();
	}
	return 0;
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse) {
		LastX = xpos;
		LastY = ypos;
		firstMouse = false;
	}

	float xOffSet = xpos - LastX;
	float yOffset = LastY - ypos;
	LastX = xpos;
	LastY = ypos;

	float sensitivity = 0.1f;
	xOffSet *= sensitivity;
	yOffset *= sensitivity;

	yaw += xOffSet;
	pitch += yOffset;

	if (pitch > 89.0f) {
		pitch = 89.0f;
	}
	if (pitch < -89.0f) {
		pitch = -89.0f;
	}

	glm::vec3 direction;
	direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction.y = sin(glm::radians(pitch));
	direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	cameraFront = glm::normalize(direction);
}
