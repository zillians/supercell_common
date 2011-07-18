/**
 * Zillians MMO
 * Copyright (C) 2007-2010 Zillians.com, Inc.
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
 * @date Jul 11, 2011 sdk - Initial version created.
 */

#include "utility/UnicodeUtil.h"

#define BOOST_UTF8_BEGIN_NAMESPACE namespace zillians {
#define BOOST_UTF8_END_NAMESPACE }
#define BOOST_UTF8_DECL

#include <boost/detail/utf8_codecvt_facet.hpp>
#include "utility/detail/boost/utf8_codecvt_facet.cpp"

namespace zillians {

std::locale& get_posix_locale()
{
	static std::locale default_locale("POSIX");
	return default_locale;
}

std::locale& get_c_locale()
{
	static std::locale default_locale("C");
	return default_locale;
}

std::locale& get_utf8_locale()
{
	static utf8_codecvt_facet* utf8_facet = new utf8_codecvt_facet;
	static std::locale utf8_locale(std::locale(), utf8_facet);
	return utf8_locale;
}

std::locale& get_default_locale()
{
	static std::locale default_locale("");
	return default_locale;
}

void utf8_to_ucs4(const std::string& input, std::wstring& output)
{
	typedef boost::u8_to_u32_iterator<std::string::const_iterator> iterator_type;
	iterator_type first(input.begin());
	iterator_type last(input.end());
	std::copy(first, last, std::back_inserter(output));
}

}
