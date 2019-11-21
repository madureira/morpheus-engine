/*
Title: Sprite Batching
File Name: shader.cpp
Copyright ? 2016
Author: David Erbelding
Written under the supervision of David I. Schwartz, Ph.D., and
supported by a professional development seed grant from the B. Thomas
Golisano College of Computing & Information Sciences
(https://www.rit.edu/gccis) at the Rochester Institute of Technology.

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or (at
your option) any later version.

This program is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once
#include "shader.h"
#include <iostream>
#include <fstream>

Shader::Shader()
{
}

Shader::~Shader()
{
	// Only delete the shader index if it was initialized successfully.
	if (m_shader != 0)
	{
		glDeleteShader(m_shader);
	}
}

bool Shader::InitFromFile(std::string filePath, GLenum shaderType)
{

	std::ifstream file(filePath);

	// Check if the file exists
	if (!file.good())
	{
		// If we encounter an error, print a message and return false.
		std::cout << "Can't read file: " << filePath << std::endl;
		return false;
	}

	// ifstream internally keeps track of where in the file.

	// Here we find the end of the file.
	file.seekg(0, std::ios::end);

	// Make a string and set its size equal to the length of the file.
	std::string shaderCode;
	shaderCode.resize((size_t)file.tellg());

	// Go back to the beginning of the file.
	file.seekg(0, std::ios::beg);

	// Read the file into the string until we reach the end of the string.
	file.read(&shaderCode[0], shaderCode.size());

	// Close the file.
	file.close();

	// Init using the string.
	return InitFromString(shaderCode, shaderType);
}

bool Shader::InitFromString(std::string shaderCode, GLenum shaderType)
{
	m_type = shaderType;
	m_shader = glCreateShader(shaderType);

	// Get the char* and length
	const char* shaderCodePointer = shaderCode.data();
	int shaderCodeLength = shaderCode.size();

	// Set the source code and compile.
	glShaderSource(m_shader, 1, &shaderCodePointer, &shaderCodeLength);
	glCompileShader(m_shader);

	GLint isCompiled;

	// Check if the fragmentShader compiles:
	// If it failed, print an error and delete it.
	glGetShaderiv(m_shader, GL_COMPILE_STATUS, &isCompiled);

	if (!isCompiled)
	{
		char infolog[1024];
		glGetShaderInfoLog(m_shader, 1024, NULL, infolog);
		std::cout << "Shader compile failed with error: " << std::endl << infolog << std::endl;

		// Delete the shader, and set the index to zero so that this object knows it doesn't have a shader.
		glDeleteShader(m_shader);
		m_shader = 0;
		return false;
	}
	else
	{
		return true;
	}
}


void Shader::AttachTo(GLuint program)
{
	// Attach the owned shader to the given shader program.
	if (m_shader != 0)
	{
		glAttachShader(program, m_shader);
	}
	else
	{
		// Print an error if trying to attach an uninitialized shader.
		std::cout << "Failed to attach shader: Shader not initialized." << std::endl;
	}
}
