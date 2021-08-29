#pragma once
#include "main.h"

ObjData MoonObjData;

void InitializeMoon() {

	LoadObjFile(&MoonObjData, "moon/Earth.obj");
	GLfloat bunnyOffsets[] = { -5.5f, 0.0f, 0.0f };

	LoadObjToMemory(
		&MoonObjData,
		0.35f,
		bunnyOffsets

	);
}

void BindMoonArray() {
	glBindVertexArray(MoonObjData.vaoId);
}

void DrawMoon() {

	glActiveTexture(GL_TEXTURE0);
	GLuint backPackTexture = MoonObjData.textures[MoonObjData.materials[0].diffuse_texname];
	glBindTexture(GL_TEXTURE_2D, backPackTexture);

	glDrawElements(GL_TRIANGLES, MoonObjData.numFaces, GL_UNSIGNED_INT, (void*)0);

	glBindTexture(GL_TEXTURE_2D, 0);


}