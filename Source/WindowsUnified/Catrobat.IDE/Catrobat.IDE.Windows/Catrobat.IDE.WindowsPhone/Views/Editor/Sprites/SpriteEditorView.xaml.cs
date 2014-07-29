﻿using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Navigation;
using Catrobat.IDE.Core.Models;
using Catrobat.IDE.Core.Services;
using Catrobat.IDE.Core.UI;
using Catrobat.IDE.Core.ViewModels;
using Catrobat.IDE.Core.ViewModels.Editor.Sprites;
using Windows.UI.Xaml;
using Catrobat.IDE.WindowsShared.Services;

namespace Catrobat.IDE.WindowsPhone.Views.Editor.Sprites
{
    public partial class SpriteEditorView
    {
        private readonly SpriteEditorViewModel _viewModel = ((ViewModelLocator)ServiceLocator.ViewModelLocator).SpriteEditorViewModel;

        public SpriteEditorView()
        {
            InitializeComponent();
        }

        protected override void OnNavigatedTo(NavigationEventArgs e)
        {
            //((SoundPlayerServiceWindowsShared) ServiceLocator.SoundPlayerService).
            //    SetMediaElement(MediaElementSound);

            base.OnNavigatedTo(e);
        }

        protected override void OnNavigatedFrom(NavigationEventArgs e)
        {
            //ServiceLocator.SoundPlayerService.Clear();

            base.OnNavigatedFrom(e);
        }

        //private void PlayPauseButtonSound_OnPlayStateChanged(PlayPauseButton button, 
        //    PlayPauseButtonState state)
        //{
        //    var sound = (Sound)button.DataContext;

        //    if (state == PlayPauseButtonState.Play)
        //    {
        //        _viewModel.PlaySoundCommand.Execute(sound);
        //    }
        //    else
        //    {
        //        _viewModel.StopSoundCommand.Execute(sound);
        //    }
        //}

        //private void reorderListBoxScriptBricks_Loaded(object sender, RoutedEventArgs e)
        //{
        //    if (_viewModel.SelectedBrick != null)
        //    {
        //        ReorderListBoxScriptBricks.ScrollIntoView(_viewModel.SelectedBrick);
        //        _viewModel.SelectedBrick = null;
        //    }
        //}
    }
}
