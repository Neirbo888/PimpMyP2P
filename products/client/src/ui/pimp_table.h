/*
 ==============================================================================
 
 pimp_table.h
 Created: 20 Nov 2014 4:23:38pm
 Author:  Adrien Tisseraud
 
 ==============================================================================
 */

#ifndef PIMP_TABLE_H_INCLUDED
#define PIMP_TABLE_H_INCLUDED

#include "JuceHeader.h"
#include "products/common/files/peer_file.h"

/// @class PimpTable
/// @brief Displays a search result received from the Tracker, double clicking
/// on a file starts a transfer between one or multiple peers
class PimpTable
: public juce::Component,
  public juce::TableListBoxModel,
  public juce::ChangeBroadcaster
{
public:
  /// @brief Constructor
  PimpTable(juce::ChangeListener* listener);
  
  /// @brief Destructor
  ~PimpTable();
  
  /// @brief Load data received
  void loadData(juce::Array<PeerFile> files);
  
  /// @brief Returns the current number of rows in the table
  int getNumRows();
  
  /// @brief Resize callback
  void resized();
  
  /// @brief This is overloaded from TableListBoxModel, and must paint any cells
  /// that aren't using custom components.
  void paintCell (Graphics& g, int rowNumber, int columnId, int width,
                  int height, bool rowIsSelected);
  
  /// @brief This is overloaded from TableListBoxModel, and should fill in the
  /// background of the whole row
  void paintRowBackground (Graphics& g, int rowNumber, int width, int height,
                           bool rowIsSelected);
  
  /// @brief A utility method to search our XML for the attribute that matches
  /// a column ID
  String getAttributeNameForColumnId (const int columnId) const;
  
  /// @brief Return the PeerFile that is selected
  const PeerFile& getSelectedFile();
  
  /// @brief Callback called every time an element is double clicked
  void cellDoubleClicked(int rowNumber, int columnId, const MouseEvent &);
  
private:
  /// @brief The table component itself
  TableListBox _table;
  /// @brief The number of rows that are to be painted
  int _numRows;
  /// @brief This is the XML data received from the Tracker
  juce::Array<PeerFile> _files;
};


#endif  // PIMP_TABLE_H_INCLUDED
