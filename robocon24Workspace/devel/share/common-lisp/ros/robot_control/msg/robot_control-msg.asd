
(cl:in-package :asdf)

(defsystem "robot_control-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "machine_status" :depends-on ("_package_machine_status"))
    (:file "_package_machine_status" :depends-on ("_package"))
    (:file "msg4pid" :depends-on ("_package_msg4pid"))
    (:file "_package_msg4pid" :depends-on ("_package"))
  ))