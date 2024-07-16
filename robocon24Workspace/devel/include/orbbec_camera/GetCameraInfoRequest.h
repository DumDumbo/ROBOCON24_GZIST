// Generated by gencpp from file orbbec_camera/GetCameraInfoRequest.msg
// DO NOT EDIT!


#ifndef ORBBEC_CAMERA_MESSAGE_GETCAMERAINFOREQUEST_H
#define ORBBEC_CAMERA_MESSAGE_GETCAMERAINFOREQUEST_H


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
struct GetCameraInfoRequest_
{
  typedef GetCameraInfoRequest_<ContainerAllocator> Type;

  GetCameraInfoRequest_()
    {
    }
  GetCameraInfoRequest_(const ContainerAllocator& _alloc)
    {
  (void)_alloc;
    }







  typedef boost::shared_ptr< ::orbbec_camera::GetCameraInfoRequest_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::orbbec_camera::GetCameraInfoRequest_<ContainerAllocator> const> ConstPtr;

}; // struct GetCameraInfoRequest_

typedef ::orbbec_camera::GetCameraInfoRequest_<std::allocator<void> > GetCameraInfoRequest;

typedef boost::shared_ptr< ::orbbec_camera::GetCameraInfoRequest > GetCameraInfoRequestPtr;
typedef boost::shared_ptr< ::orbbec_camera::GetCameraInfoRequest const> GetCameraInfoRequestConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::orbbec_camera::GetCameraInfoRequest_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::orbbec_camera::GetCameraInfoRequest_<ContainerAllocator> >::stream(s, "", v);
return s;
}


} // namespace orbbec_camera

namespace ros
{
namespace message_traits
{





template <class ContainerAllocator>
struct IsFixedSize< ::orbbec_camera::GetCameraInfoRequest_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::orbbec_camera::GetCameraInfoRequest_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::orbbec_camera::GetCameraInfoRequest_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::orbbec_camera::GetCameraInfoRequest_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::orbbec_camera::GetCameraInfoRequest_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::orbbec_camera::GetCameraInfoRequest_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::orbbec_camera::GetCameraInfoRequest_<ContainerAllocator> >
{
  static const char* value()
  {
    return "d41d8cd98f00b204e9800998ecf8427e";
  }

  static const char* value(const ::orbbec_camera::GetCameraInfoRequest_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0xd41d8cd98f00b204ULL;
  static const uint64_t static_value2 = 0xe9800998ecf8427eULL;
};

template<class ContainerAllocator>
struct DataType< ::orbbec_camera::GetCameraInfoRequest_<ContainerAllocator> >
{
  static const char* value()
  {
    return "orbbec_camera/GetCameraInfoRequest";
  }

  static const char* value(const ::orbbec_camera::GetCameraInfoRequest_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::orbbec_camera::GetCameraInfoRequest_<ContainerAllocator> >
{
  static const char* value()
  {
    return "\n"
;
  }

  static const char* value(const ::orbbec_camera::GetCameraInfoRequest_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::orbbec_camera::GetCameraInfoRequest_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream&, T)
    {}

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct GetCameraInfoRequest_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::orbbec_camera::GetCameraInfoRequest_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream&, const std::string&, const ::orbbec_camera::GetCameraInfoRequest_<ContainerAllocator>&)
  {}
};

} // namespace message_operations
} // namespace ros

#endif // ORBBEC_CAMERA_MESSAGE_GETCAMERAINFOREQUEST_H
