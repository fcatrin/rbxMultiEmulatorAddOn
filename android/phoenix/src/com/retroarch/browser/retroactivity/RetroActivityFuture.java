package com.retroarch.browser.retroactivity;

import retrobox.utils.ImmersiveModeSetter;
import retrobox.vinput.Mapper;
import android.os.Handler;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;

public final class RetroActivityFuture extends RetroActivityCamera {

	@Override
	public void onResume() {
		super.onResume();

		ImmersiveModeSetter.postImmersiveMode(new Handler(), getWindow(), isStableLayout());
	}
	
    private void setImmersiveMode() {
    	ImmersiveModeSetter.get().setImmersiveMode(getWindow(), isStableLayout());
	}

	private boolean isStableLayout() {
		return Mapper.hasGamepads();
	}
	
	enum EventCommand {
		QUIT,
		RESET,
		LOAD_STATE,
		SAVE_STATE,
		SAVE_SLOT_PLUS,
		SAVE_SLOT_MINUS,
		SWAP_DISK
	}
	
	public static native void eventCommand(int command);

	
	static final private int CANCEL_ID = Menu.FIRST;
    static final private int LOAD_ID = Menu.FIRST +1;
    static final private int SAVE_ID = Menu.FIRST +2;
    static final private int QUIT_ID = Menu.FIRST +3;
    static final private int RESET_ID = Menu.FIRST +4;
    static final private int SAVE_SLOT_PLUS  = Menu.FIRST +5;
    static final private int SAVE_SLOT_MINUS = Menu.FIRST +6;
    static final private int SWAP_ID = Menu.FIRST +7;
    
    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        super.onCreateOptionsMenu(menu);

        menu.add(0, CANCEL_ID, 0, "Cancel");
        menu.add(0, SAVE_ID, 0, "Save State");
        menu.add(0, LOAD_ID, 0, "Load State");
        menu.add(0, SAVE_SLOT_PLUS, 0, "Next save slot");
        menu.add(0, SAVE_SLOT_MINUS, 0, "Prev save slot");
        if (getIntent().hasExtra("MULTIDISK")) {
        	menu.add(0, SWAP_ID, 0, "Swap Disk");
        }
        menu.add(0, RESET_ID, 0, "Reset");
        menu.add(0, QUIT_ID, 0, "Quit");
        
        return true;
    }
    
    @Override
    public boolean onMenuItemSelected(int featureId, MenuItem item) {
    	if (item != null) {
	        switch (item.getItemId()) {
	        case LOAD_ID   : uiLoadState(); return true;
	        case SAVE_ID   : uiSaveState(); return true;
	        case SAVE_SLOT_PLUS   : uiNextSaveSlot(); return true;
	        case SAVE_SLOT_MINUS  : uiPrevSaveSlot(); return true;
	        case SWAP_ID  : uiSwapDisk(); return true;
	        case RESET_ID  : uiReset(); return true;
	        case QUIT_ID   : uiQuit(); return true;
	        case CANCEL_ID : return true;
	        }
    	}
        return super.onMenuItemSelected(featureId, item);
    }
	
    private void uiQuit() {
    	eventCommand(EventCommand.QUIT.ordinal());
	}

	private void uiReset() {
		eventCommand(EventCommand.RESET.ordinal());
	}

	private void uiSaveState() {
		eventCommand(EventCommand.SAVE_STATE.ordinal());
	}

	private void uiLoadState() {
		eventCommand(EventCommand.LOAD_STATE.ordinal());
	}

	private void uiNextSaveSlot() {
		eventCommand(EventCommand.SAVE_SLOT_PLUS.ordinal());
	}
	
	private void uiPrevSaveSlot() {
		eventCommand(EventCommand.SAVE_SLOT_MINUS.ordinal());
	}
	
	private void uiSwapDisk() {
		eventCommand(EventCommand.SWAP_DISK.ordinal());
	}

	@Override
	public boolean onMenuOpened(int featureId, Menu menu) {
		onPause();
		return super.onMenuOpened(featureId, menu);
	}

	@Override
	public void onOptionsMenuClosed(Menu menu) {
		onResume();
		super.onOptionsMenuClosed(menu);
	}
    
	public void showOptionsMenu() {
		runOnUiThread(new Runnable() {
			@Override
			public void run() {
				openOptionsMenu();
			}
		});
	}
	

}
