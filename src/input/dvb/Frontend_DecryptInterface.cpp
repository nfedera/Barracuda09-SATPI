/* Frontend_DecryptInterface.cpp

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
#include <input/dvb/Frontend.h>

#include <input/dvb/FrontendData.h>

namespace input {
namespace dvb {

	int Frontend::getStreamID() const {
		return _streamID;
	}

	int Frontend::getBatchCount() const {
		return _frontendData.getBatchCount();
	}

	int Frontend::getBatchParity() const {
		return _frontendData.getBatchParity();
	}

	int Frontend::getMaximumBatchSize() const {
		return _frontendData.getMaximumBatchSize();
	}

	void Frontend::decryptBatch(bool final) {
		return _frontendData.decryptBatch(final);
	}

	void Frontend::setBatchData(unsigned char *ptr, int len, int parity, unsigned char *originalPtr) {
		_frontendData.setBatchData(ptr, len, parity, originalPtr);
	}

	const dvbcsa_bs_key_s *Frontend::getKey(int parity) const {
		return _frontendData.getKey(parity);
	}

	bool Frontend::isTableCollected(int tableID) const {
		return _frontendData.isTableCollected(tableID);
	}

	void Frontend::setTableCollected(int tableID, bool collected) {
		_frontendData.setTableCollected(tableID, collected);
	}

	const unsigned char *Frontend::getTableData(int tableID) const {
		return _frontendData.getTableData(tableID);
	}

	void Frontend::collectTableData(int streamID, int tableID, const unsigned char *data) {
		_frontendData.collectTableData(streamID, tableID, data);
	}

	int  Frontend::getTableDataSize(int tableID) const {
		return _frontendData.getTableDataSize(tableID);
	}

	void Frontend::startOSCamFilterData(int pid, int demux, int filter,
		const unsigned char *filterData, const unsigned char *filterMask) {
		SI_LOG_INFO("Stream: %d, Start filter PID: %04d  demux: %d  filter: %d (data %04x mask %04x)",
			_streamID, pid, demux, filter, filterData[0], filterMask[0]);
		_frontendData.startOSCamFilterData(pid, demux, filter, filterData, filterMask);
		_frontendData.setPID(pid, true);
		// now update frontend, PID list has changed
		updateInputDevice();
   }

	void Frontend::stopOSCamFilterData(int pid, int demux, int filter) {
		SI_LOG_INFO("Stream: %d, Stop filter PID: %04d  demux: %d  filter: %d", _streamID, pid, demux, filter);
		_frontendData.stopOSCamFilterData(pid, demux, filter);
		_frontendData.setPID(pid, false);
		// now update frontend, PID list has changed
		updateInputDevice();
	}

	bool Frontend::findOSCamFilterData(const int pid, const unsigned char *tsPacket,
		int &tableID, int &filter, int &demux, std::string &filterData) {
		return _frontendData.findOSCamFilterData(pid, tsPacket, tableID, filter, demux, filterData);
	}

	void Frontend::clearOSCamFilters() {
		_frontendData.clearOSCamFilters();
	}

	void Frontend::setPMT(int pid, bool set) {
		_frontendData.setPMT(pid, set);
	}

	bool Frontend::isPMT(int pid) const {
		return _frontendData.isPMT(pid);
	}

	void Frontend::setKey(const unsigned char *cw, int parity, int index) {
		_frontendData.setKey(cw, parity, index);
	}

	void Frontend::freeKeys() {
		_frontendData.freeKeys();
	}

	void Frontend::setKeyParity(int pid, int parity) {
		_frontendData.setKeyParity(pid, parity);
	}

	int Frontend::getKeyParity(int pid) const {
		return _frontendData.getKeyParity(pid);
	}

	void Frontend::setECMInfo(int pid, int serviceID, int caID, int provID, int emcTime,
		const std::string &cardSystem, const std::string &readerName,
		const std::string &sourceName, const std::string &protocolName,
		int hops) {
		_frontendData.setECMInfo(pid, serviceID, caID, provID, emcTime,
			cardSystem, readerName, sourceName, protocolName, hops);
	}

} // namespace dvb
} // namespace input
