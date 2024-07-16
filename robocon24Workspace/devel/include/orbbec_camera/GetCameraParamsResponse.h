// Generated by gencpp from file orbbec_camera/GetCameraParamsResponse.msg
// DO NOT EDIT!


#ifndef ORBBEC_CAMERA_MESSAGE_GETCAMERAPARAMSRESPONSE_H
#define ORBBEC_CAMERA_MESSAGE_GETCAMERAPARAMSRESPONSE_H


#include <string>
#include <vector>
#include <memory>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace orbbec_camera
{
template <class ContainerAllocator>
struct GetCameraParamsResponse_
{
  typedef GetCameraParamsResponse_<ContainerAllocator> Type;

  GetCameraParamsResponse_()
    : l_intr_p()
    , r_intr_p()
    , r2l_r()
    , r2l_t()
    , success(false)
    , message()  {
      l_intr_p.assign(0.0);

      r_intr_p.assign(0.0);

      r2l_r.assign(0.0);

      r2l_t.assign(0.0);
  }
  GetCameraParamsResponse_(const ContainerAllocator& _alloc)
    : l_intr_p()
    , r_intr_p()
    , r2l_r()
    , r2l_t()
    , success(false)
    , message(_alloc)  {
  (void)_alloc;
      l_intr_p.assign(0.0);

      r_intr_p.assign(0.0);

      r2l_r.assign(0.0);

      r2l_t.assign(0.0);
  }



   typedef boost::array<float, 4>  _l_intr_p_type;
  _l_intr_p_type l_intr_p;

   typedef boost::array<float, 4>  _r_intr_p_type;
  _r_intr_p_type r_intr_p;

   typedef boost::array<float, 9>  _r2l_r_type;
  _r2l_r_type r2l_r;

   typedef boost::array<float, 3>  _r2l_t_type;
  _r2l_t_type r2l_t;

   typedef uint8_t _success_type;
  _success_type success;

   typedef std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> _message_type;
  _message_type message;





  typedef boost::shared_ptr< ::orbbec_camera::GetCameraParamsResponse_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::orbbec_camera::GetCameraParamsResponse_<ContainerAllocator> const> ConstPtr;

}; // struct GetCameraParamsResponse_

typedef ::orbbec_camera::GetCameraParamsResponse_<std::allocator<void> > GetCameraParamsResponse;

typedef boost::shared_ptr< ::orbbec_camera::GetCameraParamsResponse > GetCameraParamsResponsePtr;
typedef boost::shared_ptr< ::orbbec_camera::GetCameraParamsResponse const> GetCameraParamsResponseConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::orbbec_camera::GetCameraParamsResponse_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::orbbec_camera::GetCameraParamsResponse_<ContainerAllocator> >::stream(s, "", v);
return s;
}


template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator==(const ::orbbec_camera::GetCameraParamsResponse_<ContainerAllocator1> & lhs, const ::orbbec_camera::GetCameraParamsResponse_<ContainerAllocator2> & rhs)
{
  return lhs.l_intr_p == rhs.l_intr_p &&
    lhs.r_intr_p == rhs.r_intr_p &&
    lhs.r2l_r == rhs.r2l_r &&
    lhs.r2l_t == rhs.r2l_t &&
    lhs.success == rhs.success &&
    lhs.message == rhs.message;
}

template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator!=(const ::orbbec_camera::GetCameraParamsResponse_<ContainerAllocator1> & lhs, const ::orbbec_camera::GetCameraParamsResponse_<ContainerAllocator2> & rhs)
{
  return !(lhs == rhs);
}


} // namespace orbbec_camera

namespace ros
{
namespace message_traits
{





template <class ContainerAllocator>
struct IsFixedSize< ::orbbec_camera::GetCameraParamsResponse_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::orbbec_camera::GetCameraParamsResponse_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct IsMessage< ::orbbec_camera::GetCameraParamsResponse_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::orbbec_camera::GetCameraParamsResponse_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::orbbec_camera::GetCameraParamsResponse_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::orbbec_camera::GetCameraParamsResponse_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::orbbec_camera::GetCameraParamsResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "06621ca772ba4ac96475002c209b1554";
  }

  static const char* value(const ::orbbec_camera::GetCameraParamsResponse_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x06621ca772ba4ac9ULL;
  static const uint64_t static_value2 = 0x6475002c209b1554ULL;
};

template<class ContainerAllocator>
struct DataType< ::orbbec_camera::GetCameraParamsResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "orbbec_camera/GetCameraParamsResponse";
  }

  static const char* value(const ::orbbec_camera::GetCameraParamsResponse_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::orbbec_camera::GetCameraParamsResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "float32[4] l_intr_p\n"
"float32[4] r_intr_p\n"
"float32[9] r2l_r\n"
"float32[3] r2l_t\n"
"bool success\n"
"string message\n"
"\n"
;
  }

  static const char* value(const ::orbbec_camera::GetCameraParamsResponse_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::orbbec_camera::GetCameraParamsResponse_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.l_intr_p);
      stream.next(m.r_intr_p);
      stream.next(m.r2l_r);
      stream.next(m.r2l_t);
      stream.next(m.success);
      stream.next(m.message);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct GetCameraParamsResponse_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::orbbec_camera::GetCameraParamsResponse_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::orbbec_camera::GetCameraParamsResponse_<ContainerAllocator>& v)
  {
    s << indent << "l_intr_p[]" << std::endl;
    for (size_t i = 0; i < v.l_intr_p.size(); ++i)
    {
      s << indent << "  l_intr_p[" << i << "]: ";
      Printer<float>::stream(s, indent + "  ", v.l_intr_p[i]);
    }
    s << indent << "r_intr_p[]" << std::endl;
    for (size_t i = 0; i < v.r_intr_p.size(); ++i)
    {
      s << indent << "  r_intr_p[" << i << "]: ";
      Printer<float>::stream(s, indent + "  ", v.r_intr_p[i]);
    }
    s << indent << "r2l_r[]" << std::endl;
    for (size_t i = 0; i < v.r2l_r.size(); ++i)
    {
      s << indent << "  r2l_r[" << i << "]: ";
      Printer<float>::stream(s, indent + "  ", v.r2l_r[i]);
    }
    s << indent << "r2l_t[]" << std::endl;
    for (size_t i = 0; i < v.r2l_t.size(); ++i)
    {
      s << indent << "  r2l_t[" << i << "]: ";
      Printer<float>::stream(s, indent + "  ", v.r2l_t[i]);
    }
    s << indent << "success: ";
    Printer<uint8_t>::stream(s, indent + "  ", v.success);
    s << indent << "message: ";
    Printer<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>>::stream(s, indent + "  ", v.message);
  }
};

} // namespace message_operations
} // namespace ros

#endif // ORBBEC_CAMERA_MESSAGE_GETCAMERAPARAMSRESPONSE_H
