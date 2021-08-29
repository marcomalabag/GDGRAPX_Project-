#pragma once
#include "main.h"

ObjData CubeObjData;

void InitializeCube() {

	
	LoadObjFile(&CubeObjData, "cube.obj");
	GLfloat CubeOffsets[] = { -0.1f, 0.0f, 0.0f };
	GLfloat CubecolorOffsets[] = { 2.5f, -1.5f, 0.5f };
	LoadObjToMemory(
		&CubeObjData,
		0.5f,
		CubeOffsets
	);
}

void DrawCube() {
	glBindVertexArray(CubeObjData.vaoId);

	glDrawElements(GL_TRIANGLES, CubeObjData.numFaces, GL_UNSIGNED_INT, (void*)0);
}