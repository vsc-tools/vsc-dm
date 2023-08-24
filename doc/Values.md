
# Value Storage
The value-storage scheme is designed around a desire to store
data compactly, in large blocks, and in such a way as to 
preserve the ability to share data with generated C-ABI code.

Depending on size, a value is represented by an integer value
with max size of `uintptr_t` or some number of bytes. This is
platform-dependent behavior, with the maximum value represented
as a pure value being uint64_t on a 64-bit platform and uint32_t
on a 32-bit platform.

Currently, vsc-dm preserves independent Type and Model data 
structures, and fully-elaborates the Model tree. A future
goal is to remove the fully-elaborated model tree.

Manipulating individual values within a block of value
storage is done via the `ValRef` family of classes. These 
classes hold:
- A means to access the data type of the value (ITypeField, IDataType)
- The value, or pointer to the value
- Flags to assist in properly interpreting the value/pointer

A ValRef may have the following properties:
- It may be a pointer to data. If not, the data is held as a value
- It may hold 'Ownership' of the data, in which case it must clean up
  after the data when the reference is disposed
- It may be a composite value, in which case the datatype can be
  used retrieve references to data sub-items
- It may be a mutable or non-mutable reference. A non-mutable reference 
  may be modified without changing the source. Changing a mutable
  reference changes the source.

The `IValOps` API specifies a set of operations that all datatypes 
must implement. This includes:
- initVal - Set the initial value of the data item
- finiVal - Handle any cleanup work associated with freeing the data item
- copyVal - Create a copy of the value

During expression manipulation, common operations may include:
- Retrieve a value so as to 
- Ensure a ValRefInt is mutable, so as to adjust its width
- Create a value for the destination and ensure its size
