 #ifndef VLE_GEOMETRY_VECTOR_HPP
 #define VLE_GEOMETRY_VECTOR_HPP
 
 #include <vle/geometry/Tuple.hpp>
 
 namespace vle { namespace geometry {

     template <size_t n, class Class>
        class Vector : public vle::geometry::Tuple<n, Class>
     {
    public:
       inline Vector()
             : vle::geometry::Tuple<n, Class>()
         {}
 
         inline Vector(const Class& value)
             : vle::geometry::Tuple<n, Class>(value)
         {}
 
         inline Vector(const Class* values)
             : vle::geometry::Tuple<n, Class>(values)
         {}
 
         inline Vector(const Vector<n, Class>& t)
             : vle::geometry::Tuple<n, Class>(t)
         {}
 
         inline Vector(const std::valarray<Class>& va)
             : vle::geometry::Tuple<n, Class>(va)
         {}
 
         inline Vector<n, Class>& operator=(const Class* values)
         {
             return (Vector<n, Class>&)
                 vle::geometry::Tuple<n, Class>::operator=(values);
         }
 
         inline Vector<n, Class>& operator=(const std::valarray<Class>& va)
         {
             return (Vector<n, Class>&) std::valarray<Class>::operator=(va);
         }

         inline Vector<n, Class>& operator=(const Class& value)
         {
             return (Vector<n, Class>&) std::valarray<Class>::operator=(value);
         }
 
         inline Vector<n, Class> cross(const Vector<n, Class>& v) const
         {
             Vector<n, Class> vCross;
             if (n == 3) {
                 vCross[0] = (*this)[1] * v[2] - (*this)[2] * v[1];
                 vCross[1] = (*this)[2] * v[0] - (*this)[0] * v[2];
                 vCross[2] = (*this)[0] * v[1] - (*this)[1] * v[0];
             }
             return vCross;
         }
 
         inline Class dot(const Vector<n, Class>& v) const
         {
             return (*this * v).sum();
         }
 
         inline Class length() const
         {
             return (Class)std::sqrt(lengthSquared());
         }
 
         inline Class lengthSquared() const
         {
             return (*this * *this).sum();
         }
 
        inline Vector<n, Class>& normalize()
        {
             Class len = length();
             if(len != (Class)0)
                 operator/=(len);
            return *this;
        }
     };
 
 }} // namespace geometry vle
 
 #endif


