# This Python file uses the following encoding: utf-8
"""autogenerated by genpy from target_detection/position.msg. Do not edit."""
import codecs
import sys
python3 = True if sys.hexversion > 0x03000000 else False
import genpy
import struct


class position(genpy.Message):
  _md5sum = "6b33d03305c0dd807b7a4b6591831277"
  _type = "target_detection/position"
  _has_header = False  # flag to mark the presence of a Header object
  _full_text = """string Class   
uint16 centerX
uint16 centerY 
float64 angleX
float64 angleY
float64 distance
"""
  __slots__ = ['Class','centerX','centerY','angleX','angleY','distance']
  _slot_types = ['string','uint16','uint16','float64','float64','float64']

  def __init__(self, *args, **kwds):
    """
    Constructor. Any message fields that are implicitly/explicitly
    set to None will be assigned a default value. The recommend
    use is keyword arguments as this is more robust to future message
    changes.  You cannot mix in-order arguments and keyword arguments.

    The available fields are:
       Class,centerX,centerY,angleX,angleY,distance

    :param args: complete set of field values, in .msg order
    :param kwds: use keyword arguments corresponding to message field names
    to set specific fields.
    """
    if args or kwds:
      super(position, self).__init__(*args, **kwds)
      # message fields cannot be None, assign default values for those that are
      if self.Class is None:
        self.Class = ''
      if self.centerX is None:
        self.centerX = 0
      if self.centerY is None:
        self.centerY = 0
      if self.angleX is None:
        self.angleX = 0.
      if self.angleY is None:
        self.angleY = 0.
      if self.distance is None:
        self.distance = 0.
    else:
      self.Class = ''
      self.centerX = 0
      self.centerY = 0
      self.angleX = 0.
      self.angleY = 0.
      self.distance = 0.

  def _get_types(self):
    """
    internal API method
    """
    return self._slot_types

  def serialize(self, buff):
    """
    serialize message into buffer
    :param buff: buffer, ``StringIO``
    """
    try:
      _x = self.Class
      length = len(_x)
      if python3 or type(_x) == unicode:
        _x = _x.encode('utf-8')
        length = len(_x)
      buff.write(struct.Struct('<I%ss'%length).pack(length, _x))
      _x = self
      buff.write(_get_struct_2H3d().pack(_x.centerX, _x.centerY, _x.angleX, _x.angleY, _x.distance))
    except struct.error as se: self._check_types(struct.error("%s: '%s' when writing '%s'" % (type(se), str(se), str(locals().get('_x', self)))))
    except TypeError as te: self._check_types(ValueError("%s: '%s' when writing '%s'" % (type(te), str(te), str(locals().get('_x', self)))))

  def deserialize(self, str):
    """
    unpack serialized message in str into this message instance
    :param str: byte array of serialized message, ``str``
    """
    if python3:
      codecs.lookup_error("rosmsg").msg_type = self._type
    try:
      end = 0
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      start = end
      end += length
      if python3:
        self.Class = str[start:end].decode('utf-8', 'rosmsg')
      else:
        self.Class = str[start:end]
      _x = self
      start = end
      end += 28
      (_x.centerX, _x.centerY, _x.angleX, _x.angleY, _x.distance,) = _get_struct_2H3d().unpack(str[start:end])
      return self
    except struct.error as e:
      raise genpy.DeserializationError(e)  # most likely buffer underfill


  def serialize_numpy(self, buff, numpy):
    """
    serialize message with numpy array types into buffer
    :param buff: buffer, ``StringIO``
    :param numpy: numpy python module
    """
    try:
      _x = self.Class
      length = len(_x)
      if python3 or type(_x) == unicode:
        _x = _x.encode('utf-8')
        length = len(_x)
      buff.write(struct.Struct('<I%ss'%length).pack(length, _x))
      _x = self
      buff.write(_get_struct_2H3d().pack(_x.centerX, _x.centerY, _x.angleX, _x.angleY, _x.distance))
    except struct.error as se: self._check_types(struct.error("%s: '%s' when writing '%s'" % (type(se), str(se), str(locals().get('_x', self)))))
    except TypeError as te: self._check_types(ValueError("%s: '%s' when writing '%s'" % (type(te), str(te), str(locals().get('_x', self)))))

  def deserialize_numpy(self, str, numpy):
    """
    unpack serialized message in str into this message instance using numpy for array types
    :param str: byte array of serialized message, ``str``
    :param numpy: numpy python module
    """
    if python3:
      codecs.lookup_error("rosmsg").msg_type = self._type
    try:
      end = 0
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      start = end
      end += length
      if python3:
        self.Class = str[start:end].decode('utf-8', 'rosmsg')
      else:
        self.Class = str[start:end]
      _x = self
      start = end
      end += 28
      (_x.centerX, _x.centerY, _x.angleX, _x.angleY, _x.distance,) = _get_struct_2H3d().unpack(str[start:end])
      return self
    except struct.error as e:
      raise genpy.DeserializationError(e)  # most likely buffer underfill

_struct_I = genpy.struct_I
def _get_struct_I():
    global _struct_I
    return _struct_I
_struct_2H3d = None
def _get_struct_2H3d():
    global _struct_2H3d
    if _struct_2H3d is None:
        _struct_2H3d = struct.Struct("<2H3d")
    return _struct_2H3d
