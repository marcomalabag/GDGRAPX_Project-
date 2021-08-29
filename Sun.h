#pragma once
#include "main.h"

ObjData SunObjData;

void InitializeSun() {

	LoadObjFile(&SunObjData, "sun/Earth.obj");
	GLfloat bunnyOffsets[] = { 6.5f, 0.0f, 0.0f };

	LoadObjToMemory(
		&SunObjData,
		1.5f,
		bunnyOffsets

	);
}

void BindSunArray() {
	glBindVertexArray(SunObjData.vaoId);
}

void DrawSun() {

	glActiveTexture(GL_TEXTURE0);
	GLuint backPackTexture = SunObjData.textures[SunObjData.materials[0].diffuse_texname];
	glBindTexture(GL_TEXTURE_2D, backPackTexture);

	glDrawElements(GL_TRIANGLES, SunObjData.numFaces, GL_UNSIGNED_INT, (void*)0);

	glBindTexture(GL_TEXTURE_2D, 0);


}