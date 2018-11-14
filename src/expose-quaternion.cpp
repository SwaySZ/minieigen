#include"visitors.hpp"
//#include <boost/python/return_internal_reference.hpp>
void expose_quaternion(){
	py::class_<Quaternionr>("Quaternion","Quaternion representing rotation.\n\nSupported operations (``q`` is a Quaternion, ``v`` is a Vector3): ``q*q`` (rotation composition), ``q*=q``, ``q*v`` (rotating ``v`` by ``q``), ``q==q``, ``q!=q``.\n\nStatic attributes: ``Identity``.",py::init<>())
		.def(QuaternionVisitor<Quaternionr>())
	;
	py::class_<Rotationr>("Rotation2d","Rotation2D",py::init<>())
		.def(Rotation2DVisitor<Rotationr>())
	;
	/*py::class_<Rotationr>("Rotation2d", py::init<double>())
	    .def("angle", &Rotationr::angle,return_internal_reference<>())
	    //.def("inverse", &Rotationr::inverse, "const OneWayTranslator& getCurrentOwt() const")
	    ;
	;*/
}
