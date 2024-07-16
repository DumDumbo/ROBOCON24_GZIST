
(cl:in-package :asdf)

(defsystem "ros_stm32_serial-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "serial_topic_msgs" :depends-on ("_package_serial_topic_msgs"))
    (:file "_package_serial_topic_msgs" :depends-on ("_package"))
  ))