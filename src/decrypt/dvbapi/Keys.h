/* Keys.h

   Copyright (C) 2015, 2016 Marc Postema (mpostema09 -at- gmail.com)

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public License
   as published by the Free Software Foundation; either version 2
   of the License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
   Or, point your browser to http://www.gnu.org/copyleft/gpl.html
*/
#ifndef DECRYPT_DVBAPI_KEYS_H_INCLUDE
#define DECRYPT_DVBAPI_KEYS_H_INCLUDE DECRYPT_DVBAPI_KEYS_H_INCLUDE

#include <base/TimeCounter.h>
#include <Log.h>

#include <utility>
#include <queue>

extern "C" {
	#include <dvbcsa/dvbcsa.h>
}

namespace decrypt {
namespace dvbapi {

	///
	class Keys {
		public:
			typedef std::pair<long, dvbcsa_bs_key_s *> KeyPair;
			typedef std::queue<KeyPair> KeyQueue;

			// ================================================================
			//  -- Constructors and destructor --------------------------------
			// ================================================================
			Keys() {}

			virtual ~Keys() {}

			// ================================================================
			//  -- Other member functions -------------------------------------
			// ================================================================

		public:

			void set(const unsigned char *cw, int parity, int /*index*/) {
				dvbcsa_bs_key_s *k = dvbcsa_bs_key_alloc();
				dvbcsa_bs_key_set(cw, k);
				_key[parity].push(std::make_pair(base::TimeCounter::getTicks(), k));
			}

			const dvbcsa_bs_key_s *get(int parity) const {
				if (!_key[parity].empty()) {
					const KeyPair pair = _key[parity].front();
//					const long duration = base::TimeCounter::getTicks() - pair.first;
					return pair.second;
				} else {
					return nullptr;
				}
			}

			void remove(int parity) {
				const KeyPair pair = _key[parity].front();
				dvbcsa_bs_key_free(pair.second);
				_key[parity].pop();
			}

			void freeKeys() {
				while (!_key[0].empty()) {
					remove(0);
				}
				while (!_key[1].empty()) {
					remove(1);
				}
			}

			// ================================================================
			//  -- Data members -----------------------------------------------
			// ================================================================

		private:

			KeyQueue _key[2];
	};

} // namespace dvbapi
} // namespace decrypt

#endif // DECRYPT_DVBAPI_KEYS_H_INCLUDE
