package com.android.se.ready;

public class JCardSimJCICStoreApplet extends JCICStoreApplet {
	
	private JCardSimJCICStoreApplet() {
		super(new CryptoProviderImpl());
	}

    public static void install(byte[] bArray, short bOffset, byte bLength) {
        new JCardSimJCICStoreApplet().register();
    }

}
