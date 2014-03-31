﻿using System;
using System.ComponentModel;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Windows;
using System.Windows.Controls;
using Catrobat.IDE.Core.CatrobatObjects.Formulas;
using Catrobat.IDE.Core.CatrobatObjects.Formulas.XmlFormula;
using Catrobat.IDE.Core.FormulaEditor.Editor;
using Catrobat.IDE.Phone.Annotations;
using Catrobat.IDE.Phone.Controls.FormulaControls.Formulas;

namespace Catrobat.IDE.Phone.Controls.FormulaControls
{
    [Obsolete("Use FormulaViewer3 instead", true)]
    public partial class FormulaViewer : UserControl, INotifyPropertyChanged
    {
        private UiFormula _uiFormula;
        private XmlFormulaTree _selectedFormula;

        #region DependencyProperties

        public int NormalFontSize
        {
            get { return (int)GetValue(NormalFontSizeProperty); }
            set { SetValue(NormalFontSizeProperty, value); }
        }

        public static readonly DependencyProperty NormalFontSizeProperty = DependencyProperty.Register("NormalFontSize", typeof(int), typeof(FormulaViewer), new PropertyMetadata(0, NormalFontSizeChanged));

        private static void NormalFontSizeChanged(DependencyObject d, DependencyPropertyChangedEventArgs e)
        {
            // Code for dealing with your property changes
        }



        public int MinFontSize
        {
            get { return (int)GetValue(MinFontSizeProperty); }
            set { SetValue(MinFontSizeProperty, value); }
        }

        public static readonly DependencyProperty MinFontSizeProperty = DependencyProperty.Register("MinFontSize", typeof(int), typeof(FormulaViewer), new PropertyMetadata(0, MinFontSizeChanged));

        private static void MinFontSizeChanged(DependencyObject d, DependencyPropertyChangedEventArgs e)
        {
            // Code for dealing with your property changes
        }


        public int MaxFontSize
        {
            get { return (int)GetValue(MaxFontSizeProperty); }
            set { SetValue(MaxFontSizeProperty, value); }
        }

        public static readonly DependencyProperty MaxFontSizeProperty = DependencyProperty.Register("MaxFontSize", typeof(int), typeof(FormulaViewer), new PropertyMetadata(0, MaxFontSizeChanged));

        private static void MaxFontSizeChanged(DependencyObject d, DependencyPropertyChangedEventArgs e)
        {
            // Code for dealing with your property changes
        }


        public int CharactersInOneLineNormalFontSize
        {
            get { return (int)GetValue(CharactersInOneLineNormalFontSizeProperty); }
            set { SetValue(CharactersInOneLineNormalFontSizeProperty, value); }
        }

        public static readonly DependencyProperty CharactersInOneLineNormalFontSizeProperty = DependencyProperty.Register("CharactersInOneLineNormalFontSize", typeof(int), typeof(FormulaViewer), new PropertyMetadata(0, CharactersInOneLineNormalFontSizeChanged));

        private static void CharactersInOneLineNormalFontSizeChanged(DependencyObject d, DependencyPropertyChangedEventArgs e)
        {
            // Code for dealing with your property changes
        }


        public int LinesNormalFontSize
        {
            get { return (int)GetValue(LinesNormalFontSizeProperty); }
            set { SetValue(LinesNormalFontSizeProperty, value); }
        }

        public static readonly DependencyProperty LinesNormalFontSizeProperty = DependencyProperty.Register("LinesNormalFontSize", typeof(int), typeof(FormulaViewer), new PropertyMetadata(0, LinesNormalFontSizeChanged));

        private static void LinesNormalFontSizeChanged(DependencyObject d, DependencyPropertyChangedEventArgs e)
        {
            // Code for dealing with your property changes
        }

        public bool IsEditEnabled
        {
            get { return (bool)GetValue(IsEditEnabledProperty); }
            set { SetValue(IsEditEnabledProperty, value); }
        }

        public static readonly DependencyProperty IsEditEnabledProperty = DependencyProperty.Register("IsEditEnabled", typeof(bool), typeof(FormulaViewer), new PropertyMetadata(IsEditEnabledChanged));

        private static void IsEditEnabledChanged(DependencyObject d, DependencyPropertyChangedEventArgs e)
        {
            // TODO: implement me
            // Code for dealing with your property changes
        }



        public bool IsMultiline
        {
            get { return (bool)GetValue(IsMultilineProperty); }
            set { SetValue(IsMultilineProperty, value); }
        }

        public static readonly DependencyProperty IsMultilineProperty = DependencyProperty.Register("IsMultiline", typeof(bool), typeof(FormulaViewer), new PropertyMetadata(IsMultilineChanged));

        private static void IsMultilineChanged(DependencyObject d, DependencyPropertyChangedEventArgs e)
        {
            // TODO: implement me
            // Code for dealing with your property changes
        }



        public Formula Formula
        {
            get { return (Formula)GetValue(FormulaProperty); }
            set
            {
                SetValue(FormulaProperty, value);
                FormulaChanged();
            }
        }

        public static readonly DependencyProperty FormulaProperty = DependencyProperty.Register("Formula", typeof(Formula), typeof(FormulaViewer), new PropertyMetadata(FormulaChanged));

        private static void FormulaChanged(DependencyObject d, DependencyPropertyChangedEventArgs e)
        {
            var formula = e.NewValue as Formula;
            if (formula == null) return;

            ((FormulaViewer)d).FormulaChanged();


            //((FormulaViewer)d).FormulaViewerTreeItemRoot.UiFormula = uiFormula;



            //((FormulaViewer)d).FormulaChanged();
        }



        public bool IsAutoFontSize
        {
            get { return (bool)GetValue(IsAutoFontSizeProperty); }
            set
            {
                SetValue(IsAutoFontSizeProperty, value);
                FormulaChanged();
            }
        }

        public static readonly DependencyProperty IsAutoFontSizeProperty = DependencyProperty.Register("IsAutoFontSize", typeof(bool), typeof(FormulaViewer), new PropertyMetadata(IsAutoFontSizeChanged));

        private static void IsAutoFontSizeChanged(DependencyObject d, DependencyPropertyChangedEventArgs e)
        {
            ((FormulaViewer)d).FormulaChanged();
        }

        #endregion

        public FormulaViewer()
        {
            InitializeComponent();
        }

        public void SelectedFormulaChanged(XmlFormulaTree formula)
        {
            _selectedFormula = formula;
        }

        public void FormulaChanged()
        {
            // commented out because this class is no longer used!
            //if (Formula == null || Formula.FormulaTree.Equals(new XmlFormulaTree()))
            //    return;

            //_uiFormula = UiFormulaMappings.CreateFormula(Formula, this, Formula.FormulaTree, IsEditEnabled, _selectedFormula);
            var allParts = _uiFormula.GetAllParts();

            double fontSize = NormalFontSize;

            if (IsAutoFontSize)
            {
                double oldFontSize;
                double maxSinglePartWidth;

                int trials = 0;
                do
                {
                    trials++;
                    double linesUsedWithCurrentFontSize = 1;
                    double currentLineCharacters = 0;
                    maxSinglePartWidth = 0;
                    oldFontSize = fontSize;

                    double oldMaxLinesUsed = LinesNormalFontSize * (NormalFontSize / fontSize);

                    double currentCharactersPerLine = CharactersInOneLineNormalFontSize * (NormalFontSize / fontSize);
                    foreach (var part in allParts)
                    {
                        double partWidth = part.GetCharacterWidth();

                        currentLineCharacters += part.GetCharacterWidth();

                        if (currentLineCharacters > currentCharactersPerLine)
                        {
                            currentLineCharacters = part.GetCharacterWidth();
                            linesUsedWithCurrentFontSize++;
                        }

                        maxSinglePartWidth = Math.Max(maxSinglePartWidth, partWidth);
                    }

                    fontSize = (0.5) * oldFontSize + 0.5 * (oldFontSize * (oldMaxLinesUsed / linesUsedWithCurrentFontSize));

                } while (Math.Abs(fontSize - oldFontSize) > 7.0 && trials < 10);

                var singleLineFontSize = (int)(NormalFontSize *
                    (CharactersInOneLineNormalFontSize / maxSinglePartWidth));

                fontSize = Math.Min(fontSize, singleLineFontSize);


                if (fontSize < MinFontSize)
                    fontSize = MinFontSize;
                if (fontSize > MaxFontSize)
                    fontSize = MaxFontSize;
            }

            var allControls = allParts.Select(part => part.CreateUiControls((int)fontSize, false, false, false)).ToList(); // TODO: get error from evaluating the formula
            _uiFormula.UpdateStyles(false);

            GetPanel().Children.Clear();

            foreach (var part in allControls)
                if (part != null)
                    GetPanel().Children.Add(part);
        }

        private Panel GetPanel()
        {
            if (IsMultiline)
                return MultilinePanelContent;
            else
                return SingleLinePanelContent;
        }

        #region PropertyChanged

        public event PropertyChangedEventHandler PropertyChanged;

        [NotifyPropertyChangedInvocator]
        protected virtual void OnPropertyChanged([CallerMemberName] string propertyName = null)
        {
            PropertyChangedEventHandler handler = PropertyChanged;
            if (handler != null) handler(this, new PropertyChangedEventArgs(propertyName));
        }

        #endregion

        public SelectedFormulaInformation GetSelectedFormula()
        {
            return _uiFormula.GetSelectedFormula();
        }

        public void SetSelectedFormula(SelectedFormulaInformation formulaInformation)
        {
            _uiFormula.SetSelectedFormula(formulaInformation);
        }
    }
}
