// Generated by gencpp from file orbbec_camera/SetInt32Request.msg
// DO NOT EDIT!


#ifndef ORBBEC_CAMERA_MESSAGE_SETINT32REQUEST_H
#define ORBBEC_CAMERA_MESSAGE_SETINT32REQUEST_H


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
struct SetInt32Request_
{
  typedef SetInt32Request_<ContainerAllocator> Type;

  SetInt32Request_()
    : data(0)  {
    }
  SetInt32Request_(const ContainerAllocator& _alloc)
    : data(0)  {
  (void)_alloc;
    }



   typedef int32_t _data_type;
  _data_type data;





  typedef boost::shared_ptr< ::orbbec_camera::SetInt32Request_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::orbbec_camera::SetInt32Request_<ContainerAllocator> const> ConstPtr;

}; // struct SetInt32Request_

typedef ::orbbec_camera::SetInt32Request_<std::allocator<void> > SetInt32Request;

typedef boost::shared_ptr< ::orbbec_camera::SetInt32Request > SetInt32RequestPtr;
typedef boost::shared_ptr< ::orbbec_camera::SetInt32Request const> SetInt32RequestConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::orbbec_camera::SetInt32Request_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::orbbec_camera::SetInt32Request_<ContainerAllocator> >::stream(s, "", v);
return s;
}


template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator==(const ::orbbec_camera::SetInt32Request_<ContainerAllocator1> & lhs, const ::orbbec_camera::SetInt32Request_<ContainerAllocator2> & rhs)
{
  return lhs.data == rhs.data;
}

template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator!=(const ::orbbec_camera::SetInt32Request_<ContainerAllocator1> & lhs, const ::orbbec_camera::SetInt32Request_<ContainerAllocator2> & rhs)
{
  return !(lhs == rhs);
}


} // namespace orbbec_camera

namespace ros
{
namespace message_traits
{





template <class ContainerAllocator>
struct IsFixedSize< ::orbbec_camera::SetInt32Request_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::orbbec_camera::SetInt32Request_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::orbbec_camera::SetInt32Request_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::orbbec_camera::SetInt32Request_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::orbbec_camera::SetInt32Request_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::orbbec_camera::SetInt32Request_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::orbbec_camera::SetInt32Request_<ContainerAllocator> >
{
  static const char* value()
  {
    return "da5909fbe378aeaf85e547e830cc1bb7";
  }

  static const char* value(const ::orbbec_camera::SetInt32Request_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0xda5909fbe378aeafULL;
  static const uint64_t static_value2 = 0x85e547e830cc1bb7ULL;
};

template<class ContainerAllocator>
struct DataType< ::orbbec_camera::SetInt32Request_<ContainerAllocator> >
{
  static const char* value()
  {
    return "orbbec_camera/SetInt32Request";
  }

  static const char* value(const ::orbbec_camera::SetInt32Request_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::orbbec_camera::SetInt32Request_<ContainerAllocator> >
{
  static const char* value()
  {
    return "int32 data\n"
;
  }

  static const char* value(const ::orbbec_camera::SetInt32Request_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::orbbec_camera::SetInt32Request_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.data);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct SetInt32Request_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::orbbec_camera::SetInt32Request_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::orbbec_camera::SetInt32Request_<ContainerAllocator>& v)
  {
    s << indent << "data: ";
    Printer<int32_t>::stream(s, indent + "  ", v.data);
  }
};

} // namespace message_operations
} // namespace ros

#endif // ORBBEC_CAMERA_MESSAGE_SETINT32REQUEST_H
