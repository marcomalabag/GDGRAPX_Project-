#pragma once
#include "main.h"

ObjData teapotObjData;

void InitializeTeapot() {
	
	LoadObjFile(&teapotObjData, "teapot.obj");
	GLfloat teapotOffsets[] = { -1.7f, 0.7f, 0.0f };
	GLfloat teapotcolorOffsets[] = { 0.5f, 1.5f, 0.5f };
	LoadObjToMemory(
		&teapotObjData,
		0.09f,
		teapotOffsets,
		teapotcolorOffsets
	);
}

void DrawTeapot() {
	glBindVertexArray(teapotObjData.vaoId);

	glDrawElements(GL_TRIANGLES, teapotObjData.numFaces, GL_UNSIGNED_INT, (void*)0);
}