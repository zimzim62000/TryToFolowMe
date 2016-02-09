#ifndef UTILITY_ZIM
#define UTILITY_ZIM

#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include "Utility.h"
#include <cmath>
#include <iostream>
#include <string>

#define PI 3.14159265359

using namespace sf;
using namespace std;

class Utility
{
	public:
		Utility();
		static float Distance(Vector2f const& v1, Vector2f const& v2);
		static float DistanceCarre(Vector2f const& v1, Vector2f const& v2);
		static void dumpFloat(float const& value);
		static void dumpVecteur2(Vector2f const& v1);
		static void dumpBool(string const& text, float const& value);
		static void dumpString(string const& text);
		static int randInt(int const& rand, bool const& negative = true);
		static Color randColor();
		static float diffFloat(float const& v1, float const& v2);
		static Vector2f diffVecteur2(Vector2f const& v1, Vector2f const& v2);
		static Vector2f addVecteur2(Vector2f const& v1, Vector2f const& v2);
		static Vector2f projectionI(Vector2f const& A,Vector2f const& B,Vector2f const& C);
		static Vector2f getNormale(Vector2f const& A,Vector2f const& B,Vector2f const& C);
		static Vector2f getReBound(Vector2f const& A,Vector2f const& B);
		static bool collisionPointCircle(Vector2f const& A , Vector2f const& centerCircle, float const& radius);
		static bool collisionCircleVsLine(Vector2f const& A, Vector2f const& B, Vector2f const& centerCircle, float const& radius);
		static bool collisionCircleVsSegment(Vector2f const& A, Vector2f const& B, Vector2f const& centerCircle, float const& radius);

		static bool VecteurCollinear(Vector2f const& v1, Vector2f const& v2);

		static float normeVecteur(Vector2f const& v);
		static Vector2f normalizeVecteur(Vector2f const& v);
		static float dotProduct(Vector2f const& u, Vector2f const& v);
		static float determinant(Vector2f const& u, Vector2f const& v);
};

#endif UTILITY_ZIM
