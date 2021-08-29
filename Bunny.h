#pragma once
#include "main.h"

ObjData bunnyObjData;

void InitializeBunny() {
	
	LoadObjFile(&bunnyObjData, "earth/Earth.obj");
	GLfloat bunnyOffsets[] = { -2.5f, 0.0f, 0.0f };
	
	LoadObjToMemory(
		&bunnyObjData,
		0.5f,
		bunnyOffsets
		
	);
}

void BindArray() {
	glBindVertexArray(bunnyObjData.vaoId);
}

void DrawBunny() {
	
	glActiveTexture(GL_TEXTURE0);
	GLuint backPackTexture = bunnyObjData.textures[bunnyObjData.materials[0].diffuse_texname];
	glBindTexture(GL_TEXTURE_2D, backPackTexture);

	glDrawElements(GL_TRIANGLES, bunnyObjData.numFaces, GL_UNSIGNED_INT, (void*)0);

	glBindTexture(GL_TEXTURE_2D, 0);

	
}