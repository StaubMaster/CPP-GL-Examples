#ifndef  CHUNK_GUARDS_HPP
# define CHUNK_GUARDS_HPP

template<typename TypeObject> struct ObjectTypeAccessUniqueGuard; typedef ObjectTypeAccessUniqueGuard<Chunk> AccessLockedChunk;
template<typename TypeObject> struct ObjectTypeAccessSharedGuard; //typedef ObjectTypeAccessSharedGuard<Chunk> AccessLockedChunk;

template<typename TypeObject> struct ObjectTypeAssignUniqueGuard; typedef ObjectTypeAssignUniqueGuard<Chunk> AssignLockedChunk;
template<typename TypeObject> struct ObjectTypeAssignSharedGuard; //typedef ObjectTypeAssignSharedGuard<Chunk> AssignLockedChunk;

#endif