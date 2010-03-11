/**
 * Zillians MMO
 * Copyright (C) 2007-2009 Zillians.com, Inc.
 * For more information see http://www.zillians.com
 *
 * Zillians MMO is the library and runtime for massive multiplayer online game
 * development in utility computing model, which runs as a service for every
 * developer to build their virtual world running on our GPU-assisted machines.
 *
 * This is a close source library intended to be used solely within Zillians.com
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * COPYRIGHT HOLDER(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN
 * AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
/**
 * @date Aug 27, 2009 sdk - Initial version created.
 */

#ifndef ZILLIANS_SERVICEHUB_H_
#define ZILLIANS_SERVICEHUB_H_

#include "core-api/Common.h"
#include "core-api/SharedPtr.h"

#include <tbb/atomic.h>

/**
 * By allowing arbitrary context placement for different ContextHub instance,
 * the atomic context indexer can be stored as a member variable in ContextHub
 * to avoid link dependency (so we have a pure header class.) However this makes
 * it harder to debug and make the ContextHub object larger (memory space waste.)
 */
#define ZILLIANS_SERVICEHUB_ALLOW_ARBITRARY_CONTEXT_PLACEMENT_FOR_DIFFERENT_INSTANCE  0

namespace zillians {

/**
 * ContextHub is a universal storage for arbitrary class with constant access time.
 *
 * ContextHub utilized static template method trick to give different template type
 * a different class index, which will be used to locate the stored instance. The
 * access time is basically a small constant, since we don't use map or hash but a
 * dead simple dynamic array (std::vector).
 *
 * @note There's only one slot for each different type of object. Suppose you have
 * three different types named A, B, and C. You can only save one instance of A into
 * one instance of ContextHub. Same for B and C.
 */
class ContextHub
{
public:
	ContextHub()
	{ }

public:
	/**
	 * Save an object of type T into the universal storage.
	 *
	 * @note The ownership of the given object is transferred to this ContextHub instance.
	 * @param ctx The given object of type T
	 */
	template <typename T>
	inline void set(T* ctx)
	{
		refContext<T>() = boost::shared_ptr<T>(ctx);
	}

	/**
	 * Retrieve the object according to the given type T.
	 *
	 * @return The pointer to the stored object. Return null pointer if it's not set previously.
	 */
	template <typename T>
	inline T* get()
	{
		return boost::static_pointer_cast<T>(refContext<T>()).get();
	}

	/**
	 * Remove the previously stored object instance of type T.
	 *
	 * @note Since we use shared pointer to store the actual object pointer,
	 * ContextHub will automatically destroy the object, so you don't need
	 * to call this manually.
	 */
	template <typename T>
	inline void reset()
	{
		refContext<T>().reset();
	}

private:
	/**
	 * The magic trick to store and access context object by using static
	 * initialization to identify the index of a specific type.
	 *
	 * @return The reference to the shared pointer
	 */
	template <typename T>
	inline std::vector< boost::shared_ptr<void> >::reference refContext()
	{
		static uint32 index = msContextIndexer++;
		if(UNLIKELY(index >= mContextObjects.size()))
		{
			while(index >= mContextObjects.size())
			{
				mContextObjects.push_back(boost::shared_ptr<void>());
			}
		}

		BOOST_ASSERT(index < mContextObjects.size());
		return mContextObjects[index];
	}

	std::vector< boost::shared_ptr<void> > mContextObjects;
#if ZILLIANS_SERVICEHUB_ALLOW_ARBITRARY_CONTEXT_PLACEMENT_FOR_DIFFERENT_INSTANCE
	tbb::atomic<uint32> msContextIndexer;
#else
	static tbb::atomic<uint32> msContextIndexer;
#endif
};

}
#endif/*ZILLIANS_SERVICEHUB_H_*/
