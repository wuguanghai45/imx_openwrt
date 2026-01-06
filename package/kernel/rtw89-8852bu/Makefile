include $(TOPDIR)/rules.mk

PKG_NAME:=rtw89-8852bu
PKG_RELEASE:=1
PKG_LICENSE:=GPL-2.0-only OR BSD-3-Clause
PKG_LICENSE_FILES:=

STAMP_CONFIGURED_DEPENDS := $(STAGING_DIR)/usr/include/mac80211-backport/backport/autoconf.h

PKG_SOURCE_PROTO:=git
PKG_SOURCE_URL:=https://github.com/morrownr/rtw89.git
PKG_SOURCE_VERSION:=7da080fc2fc75709364943c7ef2b39fa5abcef77
PKG_SOURCE_DATE:=2025-12-21
PKG_MIRROR_HASH:=skip

PKG_VERSION:=$(PKG_SOURCE_DATE)
PKG_SOURCE_SUBDIR:=$(PKG_NAME)-$(PKG_VERSION)
PKG_SOURCE:=$(PKG_SOURCE_SUBDIR).tar.xz
PKG_BUILD_DIR:=$(KERNEL_BUILD_DIR)/$(PKG_SOURCE_SUBDIR)
PKG_BUILD_PARALLEL:=1

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/kernel.mk

NOSTDINC_FLAGS := \
	$(KERNEL_NOSTDINC_FLAGS) \
	-I$(PKG_BUILD_DIR) \
	-I$(PKG_BUILD_DIR)/include \
	-I$(STAGING_DIR)/usr/include/mac80211-backport \
	-I$(STAGING_DIR)/usr/include/mac80211-backport/uapi \
	-I$(STAGING_DIR)/usr/include/mac80211 \
	-I$(STAGING_DIR)/usr/include/mac80211/uapi \
	-include backport/backport.h

define KernelPackage/rtw89-8852bu
  SUBMENU:=Wireless Drivers
  TITLE:=Realtek rtw89 USB RTL8852BU driver (backports)
  DEPENDS:=@USB_SUPPORT +kmod-usb-core +kmod-mac80211 +kmod-cfg80211
  CONFLICTS:=kmod-rtw89 kmod-rtw89-pci kmod-rtw89-8851be kmod-rtw89-8852ae kmod-rtw89-8852be kmod-rtw89-8852ce
  FILES:= \
    $(PKG_BUILD_DIR)/rtw89_core_git.ko \
    $(PKG_BUILD_DIR)/rtw89_usb_git.ko \
    $(PKG_BUILD_DIR)/rtw89_8852b_common_git.ko \
    $(PKG_BUILD_DIR)/rtw89_8852b_git.ko \
    $(PKG_BUILD_DIR)/rtw89_8852bu_git.ko
  AUTOLOAD:=$(call AutoLoad,50,rtw89_core_git rtw89_usb_git rtw89_8852b_common_git rtw89_8852b_git rtw89_8852bu_git)
endef


define KernelPackage/rtw89-8852bu/description
  rtw89 upstream USB driver for RTL8852BU built against OpenWrt backports
  mac80211/cfg80211. Only the USB 8852B variant is enabled.
endef

define Build/Prepare
	$(call Build/Prepare/Default)
	rm -rf $(PKG_BUILD_DIR)/.git $(PKG_BUILD_DIR)/.gitmodules
endef

define Build/Compile
	+$(KERNEL_MAKE) \
		M="$(PKG_BUILD_DIR)" \
		NOSTDINC_FLAGS="$(NOSTDINC_FLAGS)" \
		modules
endef

define KernelPackage/rtw89-8852bu/install
	$(INSTALL_DIR) $(1)/etc/modules.d
	$(INSTALL_CONF) $(PKG_BUILD_DIR)/rtw89.conf $(1)/etc/modules.d/rtw89-usb
	$(INSTALL_DIR) $(1)/lib/firmware/rtw89
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/firmware/rtw8852b_fw-1.bin $(1)/lib/firmware/rtw89/rtw8852b_fw-1.bin
endef

$(eval $(call KernelPackage,rtw89-8852bu))
