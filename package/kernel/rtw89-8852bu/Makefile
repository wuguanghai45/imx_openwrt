include $(TOPDIR)/rules.mk
include $(INCLUDE_DIR)/kernel.mk
include $(INCLUDE_DIR)/package.mk

PKG_NAME:=rtw89-8852bu
PKG_RELEASE:=1
PKG_LICENSE:=GPL-2.0-only OR BSD-3-Clause
PKG_LICENSE_FILES:=

PKG_SOURCE_PROTO:=git
PKG_SOURCE_URL:=https://github.com/morrownr/rtw89.git
PKG_SOURCE_VERSION:=7da080fc2fc75709364943c7ef2b39fa5abcef77
PKG_SOURCE_DATE:=2025-12-21
PKG_MIRROR_HASH:=skip

PKG_VERSION:=$(PKG_SOURCE_DATE)
PKG_BUILD_DIR:=$(KERNEL_BUILD_DIR)/$(PKG_NAME)-$(PKG_VERSION)
PKG_BUILD_PARALLEL:=1

define KernelPackage/rtw89-8852bu
  SUBMENU:=Wireless Drivers
  TITLE:=Realtek rtw89 USB RTL8852BU driver (out-of-tree)
  DEPENDS:=@USB_SUPPORT +kmod-usb-core +kmod-mac80211 +kmod-cfg80211 +rtl8852bu-firmware
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
  Out-of-tree Realtek rtw89 driver for USB RTL8852BU devices based on the
  vendor rtw89 upstreaming tree. Builds against the in-tree mac80211 stack.
endef

define Build/Compile
	+$(KERNEL_MAKE) M="$(PKG_BUILD_DIR)" modules
endef

define KernelPackage/rtw89-8852bu/install
	$(INSTALL_DIR) $(1)/etc/modules.d
	$(INSTALL_CONF) $(PKG_BUILD_DIR)/rtw89.conf $(1)/etc/modules.d/rtw89-usb
endef

$(eval $(call KernelPackage,rtw89-8852bu))
