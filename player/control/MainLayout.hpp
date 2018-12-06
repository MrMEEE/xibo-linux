#pragma once

#include "IMainLayout.hpp"

#include <vector>
#include <boost/noncopyable.hpp>

class MainLayout : public IMainLayout, private boost::noncopyable
{
public:
    MainLayout(int width, int height, std::unique_ptr<IOverlayAdaptor>&& handler);
    ~MainLayout() override;

    void scale(double scaleX, double scaleY) override;
    int width() const override;
    int height() const override;

    void setBackground(std::unique_ptr<IBackground>&& background) override;
    void addRegion(std::unique_ptr<IRegion>&& region, int x, int y) override;

    IOverlayAdaptor& handler() override;
    void show() override;

private:
    void sortReorderAndShowRegions();
    void sortAndReorderRegions();
    void sortRegionsByZorder();
    void removePreviousBackgroundIfSet();
    void scaleRegions(double scaleX, double scaleY);
    void checkRegionSize(int regionWidth, int regionHeight);
    void checkBackgroundSize(int backgroundWidth, int backgroundHeight);

private:
    std::unique_ptr<IOverlayAdaptor> m_handler;
    std::unique_ptr<IBackground> m_background;
    std::vector<std::unique_ptr<IRegion>> m_regions;

};
