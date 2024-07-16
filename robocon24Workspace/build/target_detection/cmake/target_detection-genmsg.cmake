# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "target_detection: 4 messages, 0 services")

set(MSG_I_FLAGS "-Itarget_detection:/home/dragon/robocon24Workspace/src/target_detection/msg;-Igeometry_msgs:/opt/ros/melodic/share/geometry_msgs/cmake/../msg;-Isensor_msgs:/opt/ros/melodic/share/sensor_msgs/cmake/../msg;-Istd_msgs:/opt/ros/melodic/share/std_msgs/cmake/../msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(geneus REQUIRED)
find_package(genlisp REQUIRED)
find_package(gennodejs REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(target_detection_generate_messages ALL)

# verify that message/service dependencies have not changed since configure



get_filename_component(_filename "/home/dragon/robocon24Workspace/src/target_detection/msg/position.msg" NAME_WE)
add_custom_target(_target_detection_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "target_detection" "/home/dragon/robocon24Workspace/src/target_detection/msg/position.msg" ""
)

get_filename_component(_filename "/home/dragon/robocon24Workspace/src/target_detection/msg/Locked.msg" NAME_WE)
add_custom_target(_target_detection_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "target_detection" "/home/dragon/robocon24Workspace/src/target_detection/msg/Locked.msg" "target_detection/msgLocked:std_msgs/Header"
)

get_filename_component(_filename "/home/dragon/robocon24Workspace/src/target_detection/msg/msgLocked.msg" NAME_WE)
add_custom_target(_target_detection_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "target_detection" "/home/dragon/robocon24Workspace/src/target_detection/msg/msgLocked.msg" ""
)

get_filename_component(_filename "/home/dragon/robocon24Workspace/src/target_detection/msg/Positions.msg" NAME_WE)
add_custom_target(_target_detection_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "target_detection" "/home/dragon/robocon24Workspace/src/target_detection/msg/Positions.msg" "target_detection/position:std_msgs/Header"
)

#
#  langs = gencpp;geneus;genlisp;gennodejs;genpy
#

### Section generating for lang: gencpp
### Generating Messages
_generate_msg_cpp(target_detection
  "/home/dragon/robocon24Workspace/src/target_detection/msg/position.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/target_detection
)
_generate_msg_cpp(target_detection
  "/home/dragon/robocon24Workspace/src/target_detection/msg/Locked.msg"
  "${MSG_I_FLAGS}"
  "/home/dragon/robocon24Workspace/src/target_detection/msg/msgLocked.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/target_detection
)
_generate_msg_cpp(target_detection
  "/home/dragon/robocon24Workspace/src/target_detection/msg/msgLocked.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/target_detection
)
_generate_msg_cpp(target_detection
  "/home/dragon/robocon24Workspace/src/target_detection/msg/Positions.msg"
  "${MSG_I_FLAGS}"
  "/home/dragon/robocon24Workspace/src/target_detection/msg/position.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/target_detection
)

### Generating Services

### Generating Module File
_generate_module_cpp(target_detection
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/target_detection
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(target_detection_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(target_detection_generate_messages target_detection_generate_messages_cpp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/dragon/robocon24Workspace/src/target_detection/msg/position.msg" NAME_WE)
add_dependencies(target_detection_generate_messages_cpp _target_detection_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/dragon/robocon24Workspace/src/target_detection/msg/Locked.msg" NAME_WE)
add_dependencies(target_detection_generate_messages_cpp _target_detection_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/dragon/robocon24Workspace/src/target_detection/msg/msgLocked.msg" NAME_WE)
add_dependencies(target_detection_generate_messages_cpp _target_detection_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/dragon/robocon24Workspace/src/target_detection/msg/Positions.msg" NAME_WE)
add_dependencies(target_detection_generate_messages_cpp _target_detection_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(target_detection_gencpp)
add_dependencies(target_detection_gencpp target_detection_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS target_detection_generate_messages_cpp)

### Section generating for lang: geneus
### Generating Messages
_generate_msg_eus(target_detection
  "/home/dragon/robocon24Workspace/src/target_detection/msg/position.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/target_detection
)
_generate_msg_eus(target_detection
  "/home/dragon/robocon24Workspace/src/target_detection/msg/Locked.msg"
  "${MSG_I_FLAGS}"
  "/home/dragon/robocon24Workspace/src/target_detection/msg/msgLocked.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/target_detection
)
_generate_msg_eus(target_detection
  "/home/dragon/robocon24Workspace/src/target_detection/msg/msgLocked.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/target_detection
)
_generate_msg_eus(target_detection
  "/home/dragon/robocon24Workspace/src/target_detection/msg/Positions.msg"
  "${MSG_I_FLAGS}"
  "/home/dragon/robocon24Workspace/src/target_detection/msg/position.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/target_detection
)

### Generating Services

### Generating Module File
_generate_module_eus(target_detection
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/target_detection
  "${ALL_GEN_OUTPUT_FILES_eus}"
)

add_custom_target(target_detection_generate_messages_eus
  DEPENDS ${ALL_GEN_OUTPUT_FILES_eus}
)
add_dependencies(target_detection_generate_messages target_detection_generate_messages_eus)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/dragon/robocon24Workspace/src/target_detection/msg/position.msg" NAME_WE)
add_dependencies(target_detection_generate_messages_eus _target_detection_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/dragon/robocon24Workspace/src/target_detection/msg/Locked.msg" NAME_WE)
add_dependencies(target_detection_generate_messages_eus _target_detection_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/dragon/robocon24Workspace/src/target_detection/msg/msgLocked.msg" NAME_WE)
add_dependencies(target_detection_generate_messages_eus _target_detection_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/dragon/robocon24Workspace/src/target_detection/msg/Positions.msg" NAME_WE)
add_dependencies(target_detection_generate_messages_eus _target_detection_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(target_detection_geneus)
add_dependencies(target_detection_geneus target_detection_generate_messages_eus)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS target_detection_generate_messages_eus)

### Section generating for lang: genlisp
### Generating Messages
_generate_msg_lisp(target_detection
  "/home/dragon/robocon24Workspace/src/target_detection/msg/position.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/target_detection
)
_generate_msg_lisp(target_detection
  "/home/dragon/robocon24Workspace/src/target_detection/msg/Locked.msg"
  "${MSG_I_FLAGS}"
  "/home/dragon/robocon24Workspace/src/target_detection/msg/msgLocked.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/target_detection
)
_generate_msg_lisp(target_detection
  "/home/dragon/robocon24Workspace/src/target_detection/msg/msgLocked.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/target_detection
)
_generate_msg_lisp(target_detection
  "/home/dragon/robocon24Workspace/src/target_detection/msg/Positions.msg"
  "${MSG_I_FLAGS}"
  "/home/dragon/robocon24Workspace/src/target_detection/msg/position.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/target_detection
)

### Generating Services

### Generating Module File
_generate_module_lisp(target_detection
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/target_detection
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(target_detection_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(target_detection_generate_messages target_detection_generate_messages_lisp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/dragon/robocon24Workspace/src/target_detection/msg/position.msg" NAME_WE)
add_dependencies(target_detection_generate_messages_lisp _target_detection_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/dragon/robocon24Workspace/src/target_detection/msg/Locked.msg" NAME_WE)
add_dependencies(target_detection_generate_messages_lisp _target_detection_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/dragon/robocon24Workspace/src/target_detection/msg/msgLocked.msg" NAME_WE)
add_dependencies(target_detection_generate_messages_lisp _target_detection_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/dragon/robocon24Workspace/src/target_detection/msg/Positions.msg" NAME_WE)
add_dependencies(target_detection_generate_messages_lisp _target_detection_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(target_detection_genlisp)
add_dependencies(target_detection_genlisp target_detection_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS target_detection_generate_messages_lisp)

### Section generating for lang: gennodejs
### Generating Messages
_generate_msg_nodejs(target_detection
  "/home/dragon/robocon24Workspace/src/target_detection/msg/position.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/target_detection
)
_generate_msg_nodejs(target_detection
  "/home/dragon/robocon24Workspace/src/target_detection/msg/Locked.msg"
  "${MSG_I_FLAGS}"
  "/home/dragon/robocon24Workspace/src/target_detection/msg/msgLocked.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/target_detection
)
_generate_msg_nodejs(target_detection
  "/home/dragon/robocon24Workspace/src/target_detection/msg/msgLocked.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/target_detection
)
_generate_msg_nodejs(target_detection
  "/home/dragon/robocon24Workspace/src/target_detection/msg/Positions.msg"
  "${MSG_I_FLAGS}"
  "/home/dragon/robocon24Workspace/src/target_detection/msg/position.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/target_detection
)

### Generating Services

### Generating Module File
_generate_module_nodejs(target_detection
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/target_detection
  "${ALL_GEN_OUTPUT_FILES_nodejs}"
)

add_custom_target(target_detection_generate_messages_nodejs
  DEPENDS ${ALL_GEN_OUTPUT_FILES_nodejs}
)
add_dependencies(target_detection_generate_messages target_detection_generate_messages_nodejs)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/dragon/robocon24Workspace/src/target_detection/msg/position.msg" NAME_WE)
add_dependencies(target_detection_generate_messages_nodejs _target_detection_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/dragon/robocon24Workspace/src/target_detection/msg/Locked.msg" NAME_WE)
add_dependencies(target_detection_generate_messages_nodejs _target_detection_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/dragon/robocon24Workspace/src/target_detection/msg/msgLocked.msg" NAME_WE)
add_dependencies(target_detection_generate_messages_nodejs _target_detection_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/dragon/robocon24Workspace/src/target_detection/msg/Positions.msg" NAME_WE)
add_dependencies(target_detection_generate_messages_nodejs _target_detection_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(target_detection_gennodejs)
add_dependencies(target_detection_gennodejs target_detection_generate_messages_nodejs)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS target_detection_generate_messages_nodejs)

### Section generating for lang: genpy
### Generating Messages
_generate_msg_py(target_detection
  "/home/dragon/robocon24Workspace/src/target_detection/msg/position.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/target_detection
)
_generate_msg_py(target_detection
  "/home/dragon/robocon24Workspace/src/target_detection/msg/Locked.msg"
  "${MSG_I_FLAGS}"
  "/home/dragon/robocon24Workspace/src/target_detection/msg/msgLocked.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/target_detection
)
_generate_msg_py(target_detection
  "/home/dragon/robocon24Workspace/src/target_detection/msg/msgLocked.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/target_detection
)
_generate_msg_py(target_detection
  "/home/dragon/robocon24Workspace/src/target_detection/msg/Positions.msg"
  "${MSG_I_FLAGS}"
  "/home/dragon/robocon24Workspace/src/target_detection/msg/position.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/target_detection
)

### Generating Services

### Generating Module File
_generate_module_py(target_detection
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/target_detection
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(target_detection_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(target_detection_generate_messages target_detection_generate_messages_py)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/dragon/robocon24Workspace/src/target_detection/msg/position.msg" NAME_WE)
add_dependencies(target_detection_generate_messages_py _target_detection_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/dragon/robocon24Workspace/src/target_detection/msg/Locked.msg" NAME_WE)
add_dependencies(target_detection_generate_messages_py _target_detection_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/dragon/robocon24Workspace/src/target_detection/msg/msgLocked.msg" NAME_WE)
add_dependencies(target_detection_generate_messages_py _target_detection_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/dragon/robocon24Workspace/src/target_detection/msg/Positions.msg" NAME_WE)
add_dependencies(target_detection_generate_messages_py _target_detection_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(target_detection_genpy)
add_dependencies(target_detection_genpy target_detection_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS target_detection_generate_messages_py)



if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/target_detection)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/target_detection
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()
if(TARGET geometry_msgs_generate_messages_cpp)
  add_dependencies(target_detection_generate_messages_cpp geometry_msgs_generate_messages_cpp)
endif()
if(TARGET sensor_msgs_generate_messages_cpp)
  add_dependencies(target_detection_generate_messages_cpp sensor_msgs_generate_messages_cpp)
endif()
if(TARGET std_msgs_generate_messages_cpp)
  add_dependencies(target_detection_generate_messages_cpp std_msgs_generate_messages_cpp)
endif()

if(geneus_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/target_detection)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/target_detection
    DESTINATION ${geneus_INSTALL_DIR}
  )
endif()
if(TARGET geometry_msgs_generate_messages_eus)
  add_dependencies(target_detection_generate_messages_eus geometry_msgs_generate_messages_eus)
endif()
if(TARGET sensor_msgs_generate_messages_eus)
  add_dependencies(target_detection_generate_messages_eus sensor_msgs_generate_messages_eus)
endif()
if(TARGET std_msgs_generate_messages_eus)
  add_dependencies(target_detection_generate_messages_eus std_msgs_generate_messages_eus)
endif()

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/target_detection)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/target_detection
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()
if(TARGET geometry_msgs_generate_messages_lisp)
  add_dependencies(target_detection_generate_messages_lisp geometry_msgs_generate_messages_lisp)
endif()
if(TARGET sensor_msgs_generate_messages_lisp)
  add_dependencies(target_detection_generate_messages_lisp sensor_msgs_generate_messages_lisp)
endif()
if(TARGET std_msgs_generate_messages_lisp)
  add_dependencies(target_detection_generate_messages_lisp std_msgs_generate_messages_lisp)
endif()

if(gennodejs_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/target_detection)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/target_detection
    DESTINATION ${gennodejs_INSTALL_DIR}
  )
endif()
if(TARGET geometry_msgs_generate_messages_nodejs)
  add_dependencies(target_detection_generate_messages_nodejs geometry_msgs_generate_messages_nodejs)
endif()
if(TARGET sensor_msgs_generate_messages_nodejs)
  add_dependencies(target_detection_generate_messages_nodejs sensor_msgs_generate_messages_nodejs)
endif()
if(TARGET std_msgs_generate_messages_nodejs)
  add_dependencies(target_detection_generate_messages_nodejs std_msgs_generate_messages_nodejs)
endif()

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/target_detection)
  install(CODE "execute_process(COMMAND \"/usr/bin/python\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/target_detection\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/target_detection
    DESTINATION ${genpy_INSTALL_DIR}
  )
endif()
if(TARGET geometry_msgs_generate_messages_py)
  add_dependencies(target_detection_generate_messages_py geometry_msgs_generate_messages_py)
endif()
if(TARGET sensor_msgs_generate_messages_py)
  add_dependencies(target_detection_generate_messages_py sensor_msgs_generate_messages_py)
endif()
if(TARGET std_msgs_generate_messages_py)
  add_dependencies(target_detection_generate_messages_py std_msgs_generate_messages_py)
endif()
