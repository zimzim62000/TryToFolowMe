#include "Utility.h"


Utility::Utility()
{

}

float Utility::Distance(sf::Vector2f const& v1, sf::Vector2f const& v2)
{
	float distance = sqrt(pow((v2.x-v1.x),2) + pow((v2.y-v1.y),2)) ;
	//cout << "Distance :" << distance << endl;
	return distance;
}


float Utility::DistanceCarre(sf::Vector2f const& v1, sf::Vector2f const& v2)
{
	float distance = (v2.x - v1.x)*(v2.x - v1.x) + (v2.y - v1.y)*(v2.y - v1.y);
	//cout << "Distance Carre :" << distance << endl;
	return distance;
}


void Utility::dumpBool(string const& text, float const& value)
{
	cout << text << " : " << value << endl;
}


void Utility::dumpFloat(float const& value)
{
	cout << "float :" << value << endl;
}

void Utility::dumpString(string const& text)
{
	cout << text << endl;
}


void Utility::dumpVecteur2(sf::Vector2f const& v1)
{
	cout << "vecteur - x : " << v1.x << "  - y : " << v1.y << endl;
}

int Utility::randInt(int const& value, bool const& negative)
{
	if(negative == false)
		return ( rand() % value + 1 );
	else
	{
		int v = rand() % 100 + 1, neg = v % 2, multipl;
		if(neg == 0)
			multipl = 1;
		else
			multipl = -1;
		
		return ( rand() % value + 1 ) * multipl;
	}
}


Color Utility::randColor()
{
	int color = randInt(6, false)+1;
	
	if(color == 1)
	{
		return Color::Yellow;
	}
	else if(color == 2)
	{
		return Color::Red;
	}
	else if(color == 3)
	{
		return Color::Green;
	}
	else if(color == 4)
	{
		return Color::Cyan;
	}
	else if(color == 5)
	{
		return Color::Magenta;
	}

	return Color::Blue;
}

Vector2f Utility::projectionI(Vector2f const& A,Vector2f const& B,Vector2f const& C)
{
	Vector2f u, AC;
	u.x = B.x - A.x; 
	u.y = B.y - A.y; 
	AC.x = C.x - A.x;
	AC.y = C.y - A.y;
	float ti = (u.x*AC.x + u.y*AC.y)/(u.x*u.x + u.y*u.y);
	Vector2f I;
	I.x = A.x + ti*u.x;
	I.y = A.y + ti*u.y;
	return I;
}

Vector2f Utility::getNormale(Vector2f const& A,Vector2f const& B,Vector2f const& C)
{

	Vector2f AC,u,N;
	u.x = B.x - A.x;  
	u.y = B.y - A.y;
	AC.x = C.x - A.x;  
	AC.y = C.y - A.y;
	float parenthesis = u.x*AC.y-u.y*AC.x;
	//dumpBool("Normale start :::::", true);
	//Utility::dumpFloat(parenthesis);
	//Utility::dumpVecteur2(u);
	N.x = -u.y*(parenthesis);
	N.y = u.x*(parenthesis);
	//Utility::dumpVecteur2(N);
	if(0 == abs(N.x) && 0 == abs(N.y))
	{
		return N;
	}
	//Utility::dumpVecteur2(N);
	float norme = sqrt(N.x*N.x + N.y*N.y);
	N.x/=norme;
	N.y/=norme;
	//Utility::dumpVecteur2(N);
	//dumpBool("Normale stop :::::", true);
	return N;
}


Vector2f Utility::getReBound(Vector2f const& v,Vector2f const& N)
{
	//Utility::dumpBool("rebound :", true);
	//Utility::dumpVecteur2(v);
	Vector2f v2;
	double pscal = (v.x*N.x +  v.y*N.y);
	v2.x = v.x -2*pscal*N.x;
	v2.y = v.y -2*pscal*N.y;
	//Utility::dumpVecteur2(v2);
	//Utility::dumpBool("end rebound :", true);
	return v2;
}

bool Utility::collisionPointCircle(Vector2f const& A, Vector2f const& centerCircle, float const& radius)
{
	int x = A.x, y = A.y;
	int d2 = (x-centerCircle.x)*(x-centerCircle.x) + (y-centerCircle.y)*(y-centerCircle.y);
	if (d2>radius*radius)
      return false;
   else
      return true;
}

bool Utility::collisionCircleVsLine(Vector2f const& A, Vector2f const& B, Vector2f const& centerCircle, float const& radius)
{
	Vector2f u;
	u.x = B.x - A.x;
	u.y = B.y - A.y;
	Vector2f AC;
	AC.x = centerCircle.x - A.x;
	AC.y = centerCircle.y - A.y;
	float numerateur = u.x*AC.y - u.y*AC.x;
	if (numerateur <0)
		numerateur = -numerateur;
	float denominateur = sqrt(u.x*u.x + u.y*u.y);
	float CI = numerateur / denominateur;
	if (CI < radius)
		return true;
	else
		return false;
}


bool Utility::collisionCircleVsSegment(Vector2f const& A, Vector2f const& B, Vector2f const& centerCircle, float const& radius)
{
	if(Utility::collisionCircleVsLine(A, B, centerCircle, radius) == false)
	{
		return false;
	}

	Vector2f AB,AC,BC;
	AB.x = B.x - A.x;
	AB.y = B.y - A.y;
	AC.x = centerCircle.x - A.x;
	AC.y = centerCircle.y - A.y;
	BC.x = centerCircle.x - B.x;
	BC.y = centerCircle.y - B.y;
	float pscal1 = AB.x*AC.x + AB.y*AC.y;
	float pscal2 = (-AB.x)*BC.x + (-AB.y)*BC.y;
	if (pscal1>=0 && pscal2>=0)
		return true;

	return false;

}

Vector2f Utility::addVecteur2(Vector2f const& v1, Vector2f const& v2)
{
	return v1+v2;
}

Vector2f Utility::diffVecteur2(Vector2f const& v1, Vector2f const& v2)
{
	return v1-v2;
}

float Utility::diffFloat(float const& v1, float const& v2)
{
	return v1-v2;
}

bool Utility::VecteurCollinear(Vector2f const& v1, Vector2f const& v2)
{
	return ( (v1.x*v2.y - v1.y*v2.x) == 0);
}


static bool collisionRectVsSegment(Vector2f const& A, Vector2f const& B, Vector2f const& R)
{

}

float Utility::normeVecteur(Vector2f const& v)
{
	return sqrt(v.x*v.x + v.y*v.y);
}

Vector2f Utility::normalizeVecteur(Vector2f const& v)
{
	return v / normeVecteur(v);
}

float Utility::dotProduct(Vector2f const& u, Vector2f const& v)
{
	return u.x*v.x + u.y*v.y;
}

float Utility::determinant(Vector2f const& u, Vector2f const& v)
{
	return u.x*v.y - u.y*v.x;
}
