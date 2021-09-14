#pragma once
#include "main.h"

ObjData WoodenTableData;

void InitializeWoodenTable() {
	LoadObjFile(&WoodenTableData, "WoodenTable/Wood_Table.obj");

	GLfloat GateOffsets[] = { 3.0f, 0.0f, -1.5f };

	LoadObjToMemory(
		&WoodenTableData,
		1.0f,
		GateOffsets
	);
}

void BindWoodenTable() {
	glBindVertexArray(WoodenTableData.vaoId);
}

void DrawWoodenTable() {
	glActiveTexture(GL_TEXTURE0);
	GLuint backPackTexture = WoodenTableData.textures[WoodenTableData.materials[0].diffuse_texname];
	glBindTexture(GL_TEXTURE_2D, backPackTexture);

	glActiveTexture(GL_TEXTURE1);
	GLuint normalTexture = WoodenTableData.textures[WoodenTableData.materials[0].bump_texname];
	glBindTexture(GL_TEXTURE_2D, normalTexture);

	glActiveTexture(GL_TEXTURE3);
	GLuint SecondTexture = WoodenTableData.textures[WoodenTableData.materials[1].diffuse_texname];
	glBindTexture(GL_TEXTURE_2D, SecondTexture);

	glActiveTexture(GL_TEXTURE4);
	GLuint SecondnormalTexture = WoodenTableData.textures[WoodenTableData.materials[1].bump_texname];
	glBindTexture(GL_TEXTURE_2D, SecondnormalTexture);



	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDrawElements(GL_TRIANGLES, WoodenTableData.numFaces, GL_UNSIGNED_INT, (void*)0);
	//glDisable(GL_BLEND);
	glBindTexture(GL_TEXTURE_2D, 0);
}