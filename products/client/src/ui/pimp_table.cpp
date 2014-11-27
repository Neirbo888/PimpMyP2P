/*
 ==============================================================================
 
 pimp_table.cpp
 Created: 20 Nov 2014 4:23:38pm
 Author:  Adrien Tisseraud
 
 ==============================================================================
 */

#include "products/client/src/ui/pimp_table.h"

PimpTable::PimpTable(juce::ChangeListener* listener)
: _numRows(0)
{
  // Create our table component and add it to this component..
  addAndMakeVisible (_table);
  _table.setModel (this);
  
  _table.getHeader().addColumn("Filename", 1, 100, 30, -1,
                               TableHeaderComponent::visible ||
                               TableHeaderComponent::notResizableOrSortable);
  _table.getHeader().addColumn("Size", 2, 100, 30, -1,
                               TableHeaderComponent::visible ||
                               TableHeaderComponent::notResizableOrSortable);
  _table.getHeader().addColumn("Sources", 3, 100, 30, -1,
                               TableHeaderComponent::visible ||
                               TableHeaderComponent::notResizableOrSortable);
  
  // give it a border
  _table.setColour (ListBox::outlineColourId, Colours::grey);
  _table.setOutlineThickness (1);
  
  _table.setMultipleSelectionEnabled (false);
  addChangeListener(listener);
}

PimpTable::~PimpTable() {}

void PimpTable::loadData(juce::Array<PeerFile> files)
{
  _files = files;
  _numRows = _files.size();
  _table.resized();
  _table.repaint();
  repaint();
}

int PimpTable::getNumRows()
{
  return _numRows;
}

void PimpTable::resized()
{
  // position our table with a gap around its edge
  _table.setBoundsInset (BorderSize<int> (0));
  _table.getHeader().setColumnWidth(1, getWidth() * 0.7);
  _table.getHeader().setColumnWidth(2, getWidth() * 0.15);
  _table.getHeader().setColumnWidth(3, getWidth() * 0.15);
  _table.setHeaderHeight(getHeight() * 0.08);
}

void PimpTable::paintRowBackground (Graphics& g, int rowNumber, int width,
                                         int height, bool rowIsSelected)
{
  if (rowIsSelected)
    g.fillAll (juce::Colour(0xffa5bed5));
}

void PimpTable::paintCell (Graphics& g, int rowNumber, int columnId,
                                int width, int height, bool rowIsSelected)
{
  g.setColour (Colours::black);
  g.setFont (Font ("Helvetica", 11.00f, Font::plain));
  
  juce::String text;
  
  // Name
  if (columnId == 1)
  {
    text = _files.getReference(rowNumber).getFilename();
  }
  
  // Size
  else if (columnId == 2)
  {
    text = juce::String(_files.getReference(rowNumber).getSize());
  }
  
  // Source
  else
  {
    text = juce::String(_files.getReference(rowNumber).getPeersAddresses().size());
  }
  
  g.drawText (text, 2, 0, width - 4, height, Justification::centredLeft, true);
  
  g.setColour (Colours::black.withAlpha (0.2f));
}

const PeerFile& PimpTable::getSelectedFile()
{
  return _files.getReference(_table.getSelectedRow());
}

void PimpTable::cellDoubleClicked(int rowNumber, int columnId,
                                  const MouseEvent &event)
{
  sendChangeMessage();
}