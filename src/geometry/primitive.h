/*
   FileName:      primitive.h

   Created Time:  2011-08-04 12:49:53

   Auther:        Cao Jiayin

   Email:         soraytrace@hotmail.com

   Location:      China, Shanghai

   Description:   SORT is short for Simple Open-source Ray Tracing. Anyone could checkout the source code from
                'sourceforge', https://soraytrace.svn.sourceforge.net/svnroot/soraytrace. And anyone is free to
                modify or publish the source code. It's cross platform. You could compile the source code in 
                linux and windows , g++ or visual studio 2008 is required.
*/

#ifndef	SORT_PRIMITIVE
#define	SORT_PRIMITIVE

// include header file
#include "utility/smartptr.h"
#include "bbox.h"
#include "managers/matmanager.h"
#include "material/material.h"
#include "utility/referencecount.h"
#include "intersection.h"

// pre-decleration
class	Intersection;

//////////////////////////////////////////////////////////////////
//	definition of primitive
class	Primitive
{
// public method
public:
	// constructor from a id
	Primitive( unsigned id , Material* mat , bool emissive ) { m_primitive_id = id; m_mat = mat; m_bEmissive = emissive;}
	// destructor
	virtual ~Primitive(){}

	// get the intersection between a ray and a primitive
	virtual bool GetIntersect( const Ray& r , Intersection* intersect ) const = 0;

	// get the bounding box of the primitive
	virtual const BBox&	GetBBox() const = 0;

	// delete the cache
	virtual void ClearBBoxCache();

	// get primitive id
	unsigned GetID() const { return m_primitive_id; }

	// get material
	Material* GetMaterial() const 
	{ 
		if( m_mat == 0 ) 
			return MatManager::GetSingleton().GetDefaultMat();
		return m_mat; 
	}

	// set material
	void	SetMaterial( Material* mat ) { m_mat = mat; }

	// get emissive
	Spectrum GetEmissive( const Vector& wo , const Intersection& intersect ) const;

// protected field
protected:
	// bounding box
	mutable SmartPtr<BBox> m_bbox;
	// id for the primitive
	unsigned		m_primitive_id;
	// the material
	Reference<Material>	m_mat;
	// bool emissive
	bool	m_bEmissive;
};

#endif
